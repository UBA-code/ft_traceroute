/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleReceivedProbe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:36:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/13 12:00:59 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void handleReceivedProbe(t_probe *head, struct timeval receiveTime, char *ip, int port, bool targetReached)
{
  t_probe *currentProbe = head;
  bool shouldPrint = true;

  //* print all the probes that have been received, if there is a probe that has not been received yet, stop printing.
  while (currentProbe != NULL)
  {
    if (currentProbe->port == port)
    {
      ft_strncpy(currentProbe->ip, ip, INET_ADDRSTRLEN);
      currentProbe->recvTime = receiveTime;
      if (currentProbe->seq == traceroute_struct->options.maxProbes && targetReached)
      {
        currentProbe->lastReachedProbe = targetReached;
      }
    }
    if (currentProbe->recvTime.tv_sec && shouldPrint)
    {
      float rtt = (currentProbe->recvTime.tv_sec - currentProbe->sendTime.tv_sec) * 1000.0 + (currentProbe->recvTime.tv_usec - currentProbe->sendTime.tv_usec) / 1000.0;

      if (currentProbe->seq == 1)
        printf("%2d  ", currentProbe->ttl);
      if (rtt <= traceroute_struct->options.waitTime * 1000.0)
      {
        if (strcmp(currentProbe->ip, traceroute_struct->lastPrintedIp))
        {
          printf("%-15s  ", currentProbe->ip);
          ft_strncpy(traceroute_struct->lastPrintedIp, currentProbe->ip, INET_ADDRSTRLEN);
        }
        printf("%.2fms  ", rtt);
      }
      else
        printf(" * ");
      if (currentProbe->seq == traceroute_struct->options.maxProbes)
        printf("\n");

      if (traceroute_struct->targetReached && currentProbe->lastReachedProbe)
      {
        freeResources();
        exit(0);
      }
      currentProbe = deleteProbe(&traceroute_struct->probes, currentProbe->port);
      continue;
    }
    else
    {
      shouldPrint = false;
    }
    currentProbe = currentProbe->next;
  }
}
