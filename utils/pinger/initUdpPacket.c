/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initUdpPacket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:29:58 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/05 14:56:35 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void initUdpPacket(struct udphdr *udpHeader)
{
  udpHeader->uh_dport = traceroute_struct->currentPort;
  udpHeader->uh_sum = calcCksum(udpHeader, 8);
}
