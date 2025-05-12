/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printEmptyProbes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:54:15 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 17:29:05 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void printEmptyProbes(int maxTTL, int probes)
{
  for (int i = 0; i < maxTTL; i++)
  {
    printf("%2d   ", i + 1);
    for (int j = 0; j < probes; j++)
      printf(" * ");
    printf("\n");
  }
}
