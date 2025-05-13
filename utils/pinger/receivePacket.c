/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receivePacket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:57:02 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/13 12:00:36 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void receivePacket(int sockFd)
{
  char buffer[ICMP_REPLY_LEN];
  int bytesReceived = 0;
  struct timeval replyTime = {0, 0};

  bytesReceived = recvfrom(sockFd, buffer, sizeof(buffer), 0, traceroute_struct->results->ai_addr, &traceroute_struct->results->ai_addrlen);

  if (gettimeofday(&replyTime, 0))
    ft_error(1, "gettimeofday: ", true);

  struct icmp *icmpHeader;
  struct ip *ipHeader;
  struct udphdr *udpHeader;
  char hopIp[INET_ADDRSTRLEN];

  if (bytesReceived > 0)
  {
    ipHeader = (struct ip *)buffer;
    icmpHeader = (struct icmp *)&buffer[IP_HEADER_SIZE];
    udpHeader = (struct udphdr *)&buffer[IP_HEADER_SIZE + ICMP_HEADER_SIZE + IP_HEADER_SIZE];

    uint16_t tmpCksum = icmpHeader->icmp_cksum;
    icmpHeader->icmp_cksum = 0;
    bool isValidCksum = calcCksum(icmpHeader, ntohs(ipHeader->ip_len) - (ipHeader->ip_hl) * 4) == tmpCksum;

    ft_strncpy(hopIp, inet_ntoa(ipHeader->ip_src), INET_ADDRSTRLEN);

    if (icmpHeader->icmp_type == ICMP_TIMXCEED && icmpHeader->icmp_code == ICMP_TIMXCEED_INTRANS && !strcmp(inet_ntoa(ipHeader->ip_dst), traceroute_struct->host) == 0)
    {
      handleReceivedProbe(traceroute_struct->probes, replyTime, hopIp, ntohs(udpHeader->uh_dport), false);
    }
    else if (icmpHeader->icmp_type == ICMP_UNREACH && icmpHeader->icmp_code == ICMP_UNREACH_PORT && isValidCksum)
    {
      handleReceivedProbe(traceroute_struct->probes, replyTime, hopIp, ntohs(udpHeader->uh_dport), true);
      traceroute_struct->targetReached = true;
    }
  }
}
