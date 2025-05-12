/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendPacket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:56:34 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 17:16:26 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

struct timeval sendPacket(int sockfd, struct addrinfo *addr, int ttl)
{
  struct timeval sendTime = {0, 0};
  int probSeq = (traceroute_struct->totalProbesSent + 1) % traceroute_struct->options.maxProbes; //* add one because we didn't send and increment yet

  if (!probSeq) //* mean it's last probe
    probSeq = traceroute_struct->options.maxProbes;

  if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    ft_error(1, "ft_ping: setsockopt()", true);

  addProbe(&traceroute_struct->probes, traceroute_struct->ttl, traceroute_struct->options.currentPort, probSeq);

  if (gettimeofday(&sendTime, 0))
    ft_error(1, "gettimeofday: ", true);

  char packet[32] = {0};
  memset(packet, 0, sizeof(packet));
  if (sendto(sockfd, packet, sizeof(packet), 0, addr->ai_addr, addr->ai_addrlen) == -1)
    ft_error(1, "sendto: ", true);

  traceroute_struct->options.currentPort++;
  traceroute_struct->totalProbesSent++;
  return sendTime;
}
