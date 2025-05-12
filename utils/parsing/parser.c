/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:47:44 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/09 10:01:38 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int isSupportedArgument(char arg)
{
  return (arg == '?' || arg == 'm' || arg == 'p' || arg == 'q' || arg == 'w' || arg == 'f');
}

long long numValidator(char *num)
{
  long long number = 0;
  int sign = 1;
  int signsCount = 0;

  for (size_t i = 0; i < strlen(num); i++)
  {
    if (num[i] == '+' || num[i] == '-')
      signsCount++;
    if ((!isdigit(num[i]) && num[i] != '+' && num[i] != '-') ||
        signsCount > 1)
    {
      ft_error_printf(1, "ft_traceroute: invalid value (`%s' near `%s')\n", num, num);
    }
    if (num[i] == '-')
      sign = -1;
    else if (num[i] != '+')
      number = number * 10 + num[i] - '0';
  }
  return number * sign;
}

void setSpecifiedOptions(char *arg, char ***arguments)
{
  char **argv = *arguments;

  (void)argv;
  while (*arg)
  {
    if (!isSupportedArgument(*arg))
    {
      ft_error_printf(64, "ft_traceroute: invalid option -- '%c'\n\
  Try 'traceroute -?' for more information.\n",
                      *arg);
    }
    switch (*arg)
    {
    case '?':
      traceroute_struct->options.usageIsSpecified = true;
      break;
    case 'f':
    case 'm':
    case 'p':
    case 'q':
    case 'w':
      if (*(arg + 1))
      {
        if (!isdigit(*(arg + 1)) && *(arg + 1) != '+' && *(arg + 1) != '-')
        {
          if (*arg == 'm')
            ft_error_printf(1, "ft_traceroute: invalid hops value `%s'\n", arg + 1);
          else if (*arg == 'p')
            ft_error_printf(1, "ft_traceroute: invalid port number `%s'\n", arg + 1);
          else if (*arg == 'q')
            ft_error_printf(1, "traceroute: invalid value (`%s' near `%s')\n\
Try 'traceroute --help' or 'traceroute --usage' for more information.",
                            arg + 1, arg + 1);
        }
        if (*arg == 'w' && !isdigit(*(arg + 1)))
          ft_error_printf(1, "traceroute: ridiculous waiting time `%s'\n", arg + 1);
        if (*arg == 'f' && !isdigit(*(arg + 1)))
          ft_error_printf(1, "traceroute: impossible distance `%s'\n", arg + 1);
        checkAndSetOptionAmount(*arg, arg + 1);
        return;
      }
      else
      {
        if (*(argv + 1) && argv++)
          checkAndSetOptionAmount(*arg, *argv);
        else
        {
          ft_error_printf(1, "ft_traceroute: option requires an argument -- '%c'\n\
Try 'ft_traceroute -?' for more information.\n",
                          *arg);
        }
        // * skip the packets count argument for the next loop
        (*arguments)++;
      }
      break;
    default:
      ft_error_printf(64, "ft_traceroute: invalid option -- '%c'\n\
Try 'ping -?' for more information.\n",
                      *arg);
      break;
    }
    arg++;
  }
}

void argumentsParser(int argc, char **args)
{
  bool hostFound = false;

  if (argc < 2)
  {
    ft_error(64, "\
missing host operand\n\
Try 'traceroute --help' or 'traceroute --usage' for more information.",
             false);
  }
  ++args;

  while (*args)
  {
    //* check if current argument is a flag
    if (**args == '-')
    {
      ++(*args);
      //* -- is valid
      if (**args == '-')
      {
        ++(*args);
        if (!strcmp(*args, "help") || !strcmp(*args, "h") || !strcmp(*args, "he") || !strcmp(*args, "hel") || !strcmp(*args, "help"))
          traceroute_struct->options.usageIsSpecified = true;
        else
        {
          ft_error_printf(64, "\
ft_traceroute: unrecognized option '%s'\n\
Try 'traceroute --help' for more information.\n",
                          *args);
        }
      }
      else
        setSpecifiedOptions(*args, &args);
    }
    else
    {
      traceroute_struct->host = *args;
      hostFound = true;
    }
    args++;
  }
  if (!hostFound && !traceroute_struct->options.usageIsSpecified)
  {
    ft_error(64, "\
missing host operand\n\
Try 'ft_traceroute -?' for more information.",
             false);
  }
}

void checkAndSetOptionAmount(char arg, char *value)
{
  switch (arg)
  {
  case 'f':
    traceroute_struct->ttl = numValidator(value);
    if (traceroute_struct->ttl <= 0 || traceroute_struct->ttl > 255)
      ft_error_printf(1, "ft_traceroute: impossible distance `%s'\n", value);
    break;
  case 'm':
    traceroute_struct->options.maxHops = numValidator(value);
    if (traceroute_struct->options.maxHops <= 0 || traceroute_struct->options.maxHops > 255)
      ft_error_printf(1, "ft_traceroute: invalid hops value `%s'\n", value);
    break;
  case 'p':
    traceroute_struct->options.currentPort = numValidator(value);
    if (traceroute_struct->options.currentPort <= 0 || traceroute_struct->options.currentPort > 65536)
      ft_error_printf(1, "ft_traceroute: invalid port number `%s'\n", value);
    break;
  case 'q':
    traceroute_struct->options.maxProbes = numValidator(value);
    if (traceroute_struct->options.maxProbes <= 0 || traceroute_struct->options.maxProbes > 10)
      ft_error_printf(1, "ft_traceroute: number of tries should be between 1 and 10\n");
    break;
  case 'w':
    traceroute_struct->options.waitTime = numValidator(value);
    if (traceroute_struct->options.waitTime < 0 || traceroute_struct->options.waitTime > 60)
      ft_error_printf(1, "ft_traceroute: ridiculous waiting time `%s'\n", value);
    break;
  }
}
