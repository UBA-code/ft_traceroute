/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcCksum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:31:13 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/05 11:41:05 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

uint16_t calcCksum(void *icmpHeader, int len)
{
  uint16_t *buf = (unsigned short *)icmpHeader;
  uint32_t sum = 0;

  while (len > 1)
  {
    sum += *buf++;
    len -= 2;
  }

  if (len == 1)
    sum += *(unsigned char *)buf;

  while (sum >> 16)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return ~sum;
}
