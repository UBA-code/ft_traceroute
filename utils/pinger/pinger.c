/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:46:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/07 09:34:54 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void pinger()
{
  struct timeval sendTime = {0, 0};
  char *destIp = NULL;
  bool targetReached = false;
  bool hopIpAlreadyPrinted = false;

  destIp = inet_ntoa(((struct sockaddr_in *)(traceroute_struct->results->ai_addr))->sin_addr);
  if (!destIp)
    ft_error(1, "inet_ntoa failed", false);

  printf("ft_traceroute to %s (%s), 64 hops max\n", traceroute_struct->host, destIp);

  while (!targetReached && traceroute_struct->ttl < MAX_TTL)
  {
    printf("  %d   ", traceroute_struct->ttl);
    for (int i = 0; i < 3; i++)
    {
      sendTime = sendPacket(traceroute_struct->sendSocket, traceroute_struct->results, traceroute_struct->ttl);

      targetReached = receivePacket(traceroute_struct->receiveSocket, sendTime, &hopIpAlreadyPrinted);

      resolveHostName(traceroute_struct->host, &traceroute_struct->results, "udp");

      usleep(100);
    }
    hopIpAlreadyPrinted = false;
    printf("\n");
    traceroute_struct->ttl++;
  }
  (void)sendTime;
}
