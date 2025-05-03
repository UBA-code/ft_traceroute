/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:00 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/03 17:20:45 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_traceroute.h"

traceroute *traceroute_struct;

int main(int argc, char *argv[])
{
  if (getuid() != 0)
    ft_error(1, "Please run the program with sudo", false);
  initializer();
  argumentsParser(argc, argv);

  getDestIp(traceroute_struct->host, &traceroute_struct->results);

  if (traceroute_struct->options.usageIsSpecified)
    printUsage(); //* Print usage, free resources and exit

  pinger();
  return 0;
}

void getDestIp(char *host, struct addrinfo **results)
{
  //* get the ip addr of host
  struct addrinfo hints;

  bzero(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_protocol = IPPROTO_ICMP;
  hints.ai_socktype = SOCK_RAW;

  if (getaddrinfo(host, NULL, &hints, results))
    ft_error(1, "getaddrinfo: ", true);
}
