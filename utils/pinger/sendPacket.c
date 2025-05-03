/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendPacket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:56:34 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/03 19:05:07 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_traceroute.h"

struct timeval sendPacket(int sockfd, void *data, struct addrinfo *addr, int ttl)
{
  struct timeval sendTime = {0, 0};
  struct timeval timeout = {3, 0};

  if (gettimeofday(&sendTime, 0))
    ft_error(1, "gettimeofday: ", true);

  if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)))
    ft_error(1, "ft_ping: setsockopt()", true);

  if (setsockopt(sockfd, IPPROTO_IP, SO_RCVTIMEO, &timeout, sizeof(timeout)))
    ft_error(1, "ft_ping: setsockopt()", true);

  if (sendto(sockfd, data, sizeof(data), 0, addr->ai_addr, addr->ai_addrlen) == -1)
    ft_error(1, "sendto: ", true);

  //* increment the ttl each 3 times
  if (traceroute_struct->ttl % 3 == 0)
    traceroute_struct->ttl++;
  traceroute_struct->icmpHeader.icmp_seq++;
  traceroute_struct->icmpHeader.icmp_cksum = 0;
  traceroute_struct->icmpHeader.icmp_cksum = calcCksum(&traceroute_struct->icmpHeader, sizeof(traceroute_struct->icmpHeader));
  return sendTime;
}
