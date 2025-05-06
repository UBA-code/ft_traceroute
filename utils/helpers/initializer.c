/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:53:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/06 10:39:02 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void initializer()
{
  const struct timeval timeout = {3, 0};
  traceroute_struct = malloc(sizeof(traceroute));
  if (!traceroute_struct)
    ft_error(1, "Memory allocation failed", false);
  traceroute_struct->host = NULL;
  //* first socket is for sending UDP packets
  traceroute_struct->sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  //* second socket is for receiving ICMP packets */
  traceroute_struct->receiveSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (traceroute_struct->sendSocket < 0 || traceroute_struct->receiveSocket < 0)
    ft_error(1, "Socket creation failed", false);

  if (setsockopt(traceroute_struct->receiveSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
    ft_error(1, "Set socket option failed", false);
  traceroute_struct->currentPort = BASE_PORT;
  traceroute_struct->ttl = 1;
  traceroute_struct->options.usageIsSpecified = false;
}
