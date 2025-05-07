/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:00 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/07 10:21:51 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

traceroute *traceroute_struct;

int main(int argc, char *argv[])
{
  if (getuid() != 0)
    ft_error(1, "Please run the program with sudo", false);
  initializer();
  argumentsParser(argc, argv);

  resolveHostName(traceroute_struct->host, &traceroute_struct->results, "udp");

  if (traceroute_struct->options.usageIsSpecified)
    printUsage(); //* Print usage, free resources and exit

  pinger();
  return 0;
}

void resolveHostName(char *host, struct addrinfo **results, const char *type)
{
  //* get the ip addr of host
  struct addrinfo hints;

  bzero(&hints, sizeof(hints));
  if (results && *results)
    freeaddrinfo(*results);
  if (!strcmp("udp", type))
  {
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    char *port = ft_itoa(traceroute_struct->options.currentPort);
    if (getaddrinfo(host, port, &hints, results))
      ft_error(1, "getaddrinfo: ", true);
    free(port);
  }
  else if (!strcmp("icmp", type))
  {
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_socktype = SOCK_RAW;
    if (getaddrinfo(host, NULL, &hints, results))
      ft_error(1, "getaddrinfo: ", true);
  }
}
