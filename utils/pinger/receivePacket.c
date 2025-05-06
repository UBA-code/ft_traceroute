/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receivePacket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:57:02 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/06 10:35:13 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

bool receivePacket(int sockFd, struct timeval sendTime, bool isFirstPacket)
{
  int bytesReceived = 0;
  char buffer[ICMP_REPLY_LEN];
  struct icmp *icmpHeader;
  struct ip *ipHeader;
  struct timeval replyTime = {0, 0};
  char *dstIp;

  bzero(&buffer, sizeof(buffer));

  bytesReceived = recvfrom(sockFd, buffer, sizeof(buffer), 0, traceroute_struct->results->ai_addr, &traceroute_struct->results->ai_addrlen);

  if (gettimeofday(&replyTime, 0))
    ft_error(1, "gettimeofday: ", true);

  if (bytesReceived > 0)
  {
    ipHeader = (struct ip *)buffer;
    icmpHeader = (struct icmp *)&buffer[IP_HEADER_SIZE];

    uint16_t tmpCksum = icmpHeader->icmp_cksum;
    icmpHeader->icmp_cksum = 0;
    bool isValidCksum = calcCksum(icmpHeader, ntohs(ipHeader->ip_len) - (ipHeader->ip_hl) * 4) == tmpCksum;

    dstIp = inet_ntoa(ipHeader->ip_src);
    if (!dstIp)
      ft_error(1, "inet_ntop failed", false);

    if (icmpHeader->icmp_type == ICMP_TIMXCEED && icmpHeader->icmp_code == ICMP_TIMXCEED_INTRANS)
    {
      if (isFirstPacket)
      {
        ft_putstr(dstIp);
        write(1, "\t", 2);
      }
      printf("%0.2fms  ", (replyTime.tv_sec - sendTime.tv_sec) * 1000.0 + (replyTime.tv_usec - sendTime.tv_usec) / 1000.0);
      return false;
    }
    else if (icmpHeader->icmp_type == ICMP_UNREACH && icmpHeader->icmp_code == ICMP_UNREACH_PORT && isValidCksum)
    {
      if (isFirstPacket)
      {
        ft_putstr(dstIp);
        write(1, "\t", 2);
      }
      printf("%0.2fms  ", (replyTime.tv_sec - sendTime.tv_sec) * 1000.0 + (replyTime.tv_usec - sendTime.tv_usec) / 1000.0);
      return true;
    }
  }
  return false;
}
