/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:47:44 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/05 11:36:18 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int isSupportedArgument(char arg)
{
  return (arg == '?');
  // return (arg != 'v' && arg != '?' && arg != 'c' && arg != 'q' && arg != 'd' && arg != 'W' && arg != 'w');
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
    switch (*arg)
    {
      //     case 'v':
      //       traceroute_struct->options.verboseIsSpecified = true;
      //       break;
    case '?':
      traceroute_struct->options.usageIsSpecified = true;
      break;
      //     case 'q':
      //       traceroute_struct->options.quitModeIsSpecified = true;
      //       break;
      //     case 'd':
      //       traceroute_struct->options.debugModeIsSpecified = true;
      //       break;
      //     case 'w':
      //     case 'c':
      //     case 'W':
      //       if (*(arg + 1))
      //       {
      //         if (!isdigit(*(arg + 1)) && *(arg + 1) != '+' && *(arg + 1) != '-')
      //           ft_error_printf(1, "ft_ping: invalid value (`%s' near `%s')\n", arg + 1, arg + 1);
      //         checkAndSetOptionAmount(*arg, arg + 1);
      //         return;
      //       }
      //       else
      //       {
      //         if (*(argv + 1) && argv++)
      //           checkAndSetOptionAmount(*arg, *argv);
      //         else
      //         {
      //           ft_error_printf(1, "ft_ping: option requires an argument -- '%c'\n
      // Try 'ft_ping -?' for more information.\n",
      //                           *arg);
      //         }
      //         // * skip the packets count argument for the next loop
      //         (*arguments)++;
      //       }
      //       break;
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
traceroute: missing host operand\n\
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

// void checkAndSetOptionAmount(char arg, char *value)
// {
//   if (arg == 'c')
//     traceroute_struct->options.countAmount = numValidator(value);
//   else if (arg == 'W')
//     traceroute_struct->options.timeOutAmount = numValidator(value);
//   else
//     traceroute_struct->options.stopAfterAmount = numValidator(value);
//   if (arg == 'c' && traceroute_struct->options.countAmount > 0)
//     traceroute_struct->options.countIsSpecified = true;
//   else if (arg == 'W' && IS_VALID_RANGE(traceroute_struct->options.timeOutAmount))
//     traceroute_struct->options.timeOutIsSpecified = true;
//   else if (arg == 'w' && IS_VALID_RANGE(traceroute_struct->options.stopAfterAmount))
//     traceroute_struct->options.stopAfterIsSpecified = true;

//   if (arg == 'W' && (!IS_VALID_RANGE(traceroute_struct->options.timeOutAmount)))
//   {
//     if (traceroute_struct->options.timeOutAmount == 0)
//       ft_error_printf(1, "ft_ping: option value too small: %s\n", value);
//     ft_error_printf(1, "ft_ping: option value too big: %s\n", value);
//   }

//   if (arg == 'w' && (!IS_VALID_RANGE(traceroute_struct->options.stopAfterAmount)))
//   {
//     if (traceroute_struct->options.stopAfterAmount == 0)
//       ft_error_printf(1, "ft_ping: option value too small: %s\n", value);
//     ft_error_printf(1, "ft_ping: option value too big: %s\n", value);
//   }
// }
