/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:00 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/13 15:27:34 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

traceroute *traceroute_struct;

void signalHandler(int signum)
{
  (void)signum;
  printf("\n");
  freeResources();
  exit(130);
}

int main(int argc, char *argv[])
{
  if (getuid() != 0)
    ft_error(1, "Please run the program with sudo", false);

  initializer();
  argumentsParser(argc, argv);

  signal(SIGINT, signalHandler);

  if (traceroute_struct->options.usageIsSpecified)
    printUsage(); //* Print usage, free resources and exit

  resolveHostName(traceroute_struct->host, &traceroute_struct->results, "udp");

  pinger();
  return 0;
}
