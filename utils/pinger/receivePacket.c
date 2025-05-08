/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receivePacket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:57:02 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/08 10:24:43 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

bool receivePacket(int sockFd, struct timeval sendTime, bool *isHopIpAlreadyPrinted)
{
  char buffer[ICMP_REPLY_LEN];
  int bytesReceived = 0;
  struct timeval replyTime = {0, 0};

  bytesReceived = recvfrom(sockFd, buffer, sizeof(buffer), 0, traceroute_struct->results->ai_addr, &traceroute_struct->results->ai_addrlen);
  if (gettimeofday(&replyTime, 0))
    ft_error(1, "gettimeofday: ", true);

  struct icmp *icmpHeader;
  struct ip *ipHeader;
  char hopIp[INET_ADDRSTRLEN];

  if (bytesReceived > 0)
  {
    ipHeader = (struct ip *)buffer;
    icmpHeader = (struct icmp *)&buffer[IP_HEADER_SIZE];

    uint16_t tmpCksum = icmpHeader->icmp_cksum;
    icmpHeader->icmp_cksum = 0;
    bool isValidCksum = calcCksum(icmpHeader, ntohs(ipHeader->ip_len) - (ipHeader->ip_hl) * 4) == tmpCksum;

    strncpy(hopIp, inet_ntoa(ipHeader->ip_src), INET_ADDRSTRLEN);

    if (icmpHeader->icmp_type == ICMP_TIMXCEED && icmpHeader->icmp_code == ICMP_TIMXCEED_INTRANS && !strcmp(inet_ntoa(ipHeader->ip_dst), traceroute_struct->host) == 0)
    {
      if (!(*isHopIpAlreadyPrinted))
      {
        printf("%-15s  ", hopIp);
        *isHopIpAlreadyPrinted = true;
      }
      printf("%.2fms  ", (replyTime.tv_sec - sendTime.tv_sec) * 1000.0 + (replyTime.tv_usec - sendTime.tv_usec) / 1000.0);
      return false;
    }
    else if (icmpHeader->icmp_type == ICMP_UNREACH && icmpHeader->icmp_code == ICMP_UNREACH_PORT && isValidCksum)
    {
      if (!(*isHopIpAlreadyPrinted))
      {
        printf("%-15s  ", hopIp);
        *isHopIpAlreadyPrinted = true;
      }
      printf("%.2fms  ", (replyTime.tv_sec - sendTime.tv_sec) * 1000.0 + (replyTime.tv_usec - sendTime.tv_usec) / 1000.0);
      return true;
    }
  }
  else
  {
    printf("*  ");
  }
  return false;
}
