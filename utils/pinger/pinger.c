/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:46:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/07 16:55:24 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void pinger()
{
  const struct timeval timeout = {traceroute_struct->options.waitTime, 0};

  struct timeval sendTime = {0, 0};
  char *destIp = NULL;
  bool targetReached = false;
  bool hopIpAlreadyPrinted = false;
  int i = 1;

  if (setsockopt(traceroute_struct->receiveSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
    ft_error(1, "Set socket option failed", false);

  destIp = inet_ntoa(((struct sockaddr_in *)(traceroute_struct->results->ai_addr))->sin_addr);
  if (!destIp)
    ft_error(1, "inet_ntoa failed", false);

  printf("ft_traceroute to %s (%s), %d hops max\n", traceroute_struct->host, destIp, traceroute_struct->options.maxHops);

  if (traceroute_struct->options.waitTime == 0)
  {
    printEmptyProbes(traceroute_struct->options.maxHops, traceroute_struct->options.probePackets);
    freeResources();
    exit(1);
  }
  do {
    printf("  %d   ", i);
    for (int i = 0; i < traceroute_struct->options.probePackets; i++)
    {
      sendTime = sendPacket(traceroute_struct->sendSocket, traceroute_struct->results, traceroute_struct->ttl);
      
      targetReached = receivePacket(traceroute_struct->receiveSocket, sendTime, &hopIpAlreadyPrinted);
      
      resolveHostName(traceroute_struct->host, &traceroute_struct->results, "udp");
    }
    hopIpAlreadyPrinted = false;
    printf("\n");
    traceroute_struct->ttl++;
    i++;
  }
  while (!targetReached && (traceroute_struct->ttl <= traceroute_struct->options.maxHops));
  freeResources();
}
