/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:53:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/03 17:20:25 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_traceroute.h"

void initializer()
{
  traceroute_struct = malloc(sizeof(traceroute));
  if (!traceroute_struct)
    ft_error(1, "Memory allocation failed", false);
  traceroute_struct->host = NULL;
  traceroute_struct->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (traceroute_struct->socket < 0)
    ft_error(1, "Socket creation failed", false);

  bzero(&traceroute_struct->icmpHeader, sizeof(traceroute_struct->icmpHeader));

  //* initialize the icmp header
  traceroute_struct->icmpHeader.icmp_type = ICMP_ECHO;
  traceroute_struct->icmpHeader.icmp_code = 0;
  traceroute_struct->icmpHeader.icmp_cksum = 0;
  traceroute_struct->icmpHeader.icmp_id = getpid() & 0xFFFF;
  traceroute_struct->icmpHeader.icmp_seq = 0;
  traceroute_struct->icmpHeader.icmp_cksum = calcCksum(&traceroute_struct->icmpHeader, sizeof(traceroute_struct->icmpHeader));

  traceroute_struct->ttl = 1;
  traceroute_struct->options.usageIsSpecified = false;
}
