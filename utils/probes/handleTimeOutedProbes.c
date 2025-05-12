/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleTimeOutedProbes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:16:21 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/11 14:19:14 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void handleTimeOutedProbes(t_probe *head)
{
  struct timeval currentTime;
  t_probe *currentProbe = head;
  float rtt = 0.0;
  bool shouldPrint = true; //* if true mean the older probes has priority to be printed

  if (gettimeofday(&currentTime, 0))
    ft_error(1, "gettimeofday: ", true);
  while (currentProbe != NULL)
  {
    if (shouldPrint)
    {
      rtt = (currentTime.tv_sec - currentProbe->sendTime.tv_sec) * 1000.0 + (currentTime.tv_usec - currentProbe->sendTime.tv_usec) / 1000.0;
      if (rtt > traceroute_struct->options.waitTime * 1000.0)
      {
        if (currentProbe->seq == 1)
          printf("%2d  * ", currentProbe->ttl);
        else if (currentProbe->seq > 1 && currentProbe->seq < traceroute_struct->options.maxProbes)
          printf("* ");
        else if (currentProbe->seq == traceroute_struct->options.maxProbes)
          printf("*");
        if (currentProbe->seq == traceroute_struct->options.maxProbes)
          printf("\n");
        currentProbe = deleteProbe(&traceroute_struct->probes, currentProbe->port);
        continue;
      }
      else
      {
        shouldPrint = false; //* if the current probe is not timed out yet, stop printing
      }
    }
    currentProbe = currentProbe->next;
  }
}
