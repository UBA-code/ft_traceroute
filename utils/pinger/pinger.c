/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:46:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/06 10:32:01 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void pinger()
{
  struct timeval sendTime = {0, 0};
  char *destIp = NULL;
  bool targetReached = false;

  destIp = inet_ntoa(((struct sockaddr_in *)(traceroute_struct->results->ai_addr))->sin_addr);
  if (!destIp)
    ft_error(1, "inet_ntoa failed", false);

  printf("ft_traceroute to %s (%s), 64 hops max\n", traceroute_struct->host, destIp);

  while (!targetReached && traceroute_struct->ttl < MAX_TTL)
  {
    ft_putNumber(traceroute_struct->ttl);
    write(1, "\t", 1);
    for (int i = 0; i < 3; i++)
    {
      initUdpPacket(&traceroute_struct->udpHeader);

      sendTime = sendPacket(traceroute_struct->sendSocket, &traceroute_struct->udpHeader, traceroute_struct->results, traceroute_struct->ttl);

      FD_ZERO(&traceroute_struct->readFds);
      FD_SET(traceroute_struct->receiveSocket, &traceroute_struct->readFds);
      if (select(traceroute_struct->receiveSocket + 1, &traceroute_struct->readFds, NULL, NULL, &(struct timeval){3, 0}) == -1)
        ft_error(1, "select: ", true);

      if (FD_ISSET(traceroute_struct->receiveSocket, &traceroute_struct->readFds))
      {
        targetReached = receivePacket(traceroute_struct->receiveSocket, sendTime, i == 0);
        resolveHostName(traceroute_struct->host, &traceroute_struct->results, "udp");
      }
      else
      {
        write(1, "*", 1);
        write(1, " ", 1);
      }
      // usleep(100);
    }
    printf("\n");
    traceroute_struct->ttl++;
  }
  (void)sendTime;
}
