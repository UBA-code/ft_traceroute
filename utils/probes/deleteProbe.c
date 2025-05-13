/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleteProbe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:03:20 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 08:08:37 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_probe *deleteProbe(t_probe **head, int port)
{
  t_probe *current = *head;
  t_probe *prev = NULL;
  t_probe *next = NULL;

  if (!current)
  {
    traceroute_struct->probeCount = 0;
    return NULL;
  }
  while (current)
  {
    if (current->port == port)
    {
      next = current->next;
      if (prev == NULL)
        *head = next;
      else
        prev->next = next;
      free(current);
      current = NULL;
      traceroute_struct->probeCount--;
      return next;
    }
    prev = current;
    current = current->next;
  }
  return current;
}

void printList(t_probe *head)
{
  t_probe *current = head;
  printf("===================\n");
  while (current != NULL)
  {
    printf("Port: %d, IP: %s, TTL: %d, Send Time: %ld.%06ld, Recv Time: %ld.%06ld\n",
           current->port,
           current->ip,
           current->ttl,
           current->sendTime.tv_sec,
           current->sendTime.tv_usec,
           current->recvTime.tv_sec,
           current->recvTime.tv_usec);
    current = current->next;
  }
  printf("===================\n");
}
