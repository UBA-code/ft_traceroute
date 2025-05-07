/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolveHostNames.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:30:48 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/07 16:30:54 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void resolveHostName(char *host, struct addrinfo **results, const char *type)
{
  //* get the ip addr of host
  struct addrinfo hints;

  bzero(&hints, sizeof(hints));
  if (results && *results)
  {
    freeaddrinfo(*results);
    *results = NULL;
  }
  if (!strcmp("udp", type))
  {
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    char *port = ft_itoa(traceroute_struct->options.currentPort);
    if (getaddrinfo(host, port, &hints, results))
    {
      free(port);
      ft_error(1, "unknown host", false);
    }
    free(port);
  }
  else if (!strcmp("icmp", type))
  {
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_socktype = SOCK_RAW;
    if (getaddrinfo(host, NULL, &hints, results))
      ft_error(1, "unknown host", false);
  }
}
