/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:46:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 10:24:23 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void pinger()
{
  struct timeval timeout = {1, 0};

  char *destIp = NULL;
  fd_set readSet;

  destIp = inet_ntoa(((struct sockaddr_in *)(traceroute_struct->results->ai_addr))->sin_addr);
  if (!destIp)
    ft_error(1, "inet_ntoa failed", false);

  printf("ft_traceroute to %s (%s), %d hops max, %ld byte packets\n", traceroute_struct->host, destIp, traceroute_struct->options.maxHops,
         sizeof(struct ip) + sizeof(struct udphdr) + 32); //* 32 is the size of the payload

  if (traceroute_struct->options.waitTime == 0)
  {
    printEmptyProbes(traceroute_struct->options.maxHops, traceroute_struct->options.maxProbes);
    freeResources();
    exit(1);
  }

  do
  {
    //* send 3 probes for each ttl and ensure there is 16 packets in flight
    while ((traceroute_struct->probeCount < MAX_PROBES_SIMULTANEOUS && traceroute_struct->ttl <= traceroute_struct->options.maxHops && !traceroute_struct->targetReached) ||
           !traceroute_struct->totalProbesSent ||
           (traceroute_struct->targetReached && traceroute_struct->totalProbesSent % 3 != 0))
    {
      resolveHostName(traceroute_struct->dstIp, &traceroute_struct->results, "udp");
      sendPacket(traceroute_struct->sendSocket, traceroute_struct->results, traceroute_struct->ttl);
      if ((traceroute_struct->totalProbesSent) % 3 == 0)
        traceroute_struct->ttl++;
    }

    //* iterate over the sended probes and check if there is any response
    for (int responses = traceroute_struct->probeCount; responses > 0; responses--)
    {
      FD_ZERO(&readSet);
      FD_SET(traceroute_struct->receiveSocket, &readSet);
      if (select(traceroute_struct->receiveSocket + 1, &readSet, NULL, NULL, &timeout) < 0)
        ft_error(1, "Select failed", false);
      if (FD_ISSET(traceroute_struct->receiveSocket, &readSet))
        receivePacket(traceroute_struct->receiveSocket);
    }
    //* check if there is any probe that has timed out
    handleTimeOutedProbes(traceroute_struct->probes);
  } while (traceroute_struct->ttl <= traceroute_struct->options.maxHops || traceroute_struct->probeCount > 0);
  freeResources();
}
