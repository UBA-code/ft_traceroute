/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendPacket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:56:34 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/06 17:43:17 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

struct timeval sendPacket(int sockfd, struct addrinfo *addr, int ttl)
{
  struct timeval sendTime = {0, 0};

  if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    ft_error(1, "ft_ping: setsockopt()", true);

  if (gettimeofday(&sendTime, 0))
    ft_error(1, "gettimeofday: ", true);

  if (sendto(sockfd, NULL, 0, 0, addr->ai_addr, addr->ai_addrlen) == -1)
    ft_error(1, "sendto: ", true);

  traceroute_struct->currentPort++;
  return sendTime;
}
