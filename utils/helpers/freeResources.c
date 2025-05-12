/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeResources.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:10:07 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 16:24:41 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void freeResources()
{
  if (traceroute_struct)
  {
    if (traceroute_struct->probes)
      freeProbes(&traceroute_struct->probes);
    if (traceroute_struct->sendSocket != -1)
    {
      close(traceroute_struct->sendSocket);
      traceroute_struct->sendSocket = -1;
    }
    if (traceroute_struct->results)
    {
      freeaddrinfo(traceroute_struct->results);
      traceroute_struct->results = NULL;
    }
    close(traceroute_struct->sendSocket);
    close(traceroute_struct->receiveSocket);
    free(traceroute_struct);
    traceroute_struct = NULL;
  }
}
