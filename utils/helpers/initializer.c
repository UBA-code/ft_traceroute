/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:53:41 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 17:31:23 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void initializer()
{
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

  traceroute_struct->results = NULL;

  //* set default options values
  traceroute_struct->options.currentPort = BASE_PORT;
  traceroute_struct->options.maxHops = MAX_TTL;
  traceroute_struct->options.maxProbes = DEFAULT_PROBES;
  traceroute_struct->options.usageIsSpecified = false;
  traceroute_struct->options.waitTime = DEFAULT_WAIT_TIME;

  traceroute_struct->probes = NULL;
  traceroute_struct->probeCount = 0;
  bzero(traceroute_struct->lastPrintedIp, INET_ADDRSTRLEN);
  traceroute_struct->targetReached = false;
  traceroute_struct->totalProbesSent = 0;
  bzero(traceroute_struct->dstIp, INET_ADDRSTRLEN);

  traceroute_struct->ttl = INITIAL_TTL;
}
