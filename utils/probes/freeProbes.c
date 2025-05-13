/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeProbes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:10:23 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/09 09:11:38 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void freeProbes(t_probe **head)
{
  t_probe *current = *head;
  t_probe *next;

  if (!current)
    return;
  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}
