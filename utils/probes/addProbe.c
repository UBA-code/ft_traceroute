/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addProbe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:03:20 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/11 19:04:18 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_probe *addProbe(t_probe **head, int ttl, int port, int probeSeq)
{
  t_probe *current = *head;
  t_probe *newProbe = malloc(sizeof(t_probe));
  if (!newProbe)
    return (NULL);

  gettimeofday(&newProbe->sendTime, 0);
  newProbe->recvTime = (struct timeval){0, 0};
  newProbe->ttl = ttl;
  newProbe->port = port;
  newProbe->seq = probeSeq;
  newProbe->next = NULL;
  traceroute_struct->probeCount++;
  if (!current)
  {
    *head = newProbe;
    return (newProbe);
  }
  while (current->next)
    current = current->next;
  current->next = newProbe;
  return (newProbe);
}
