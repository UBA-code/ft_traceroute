/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receivePacket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:57:02 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/03 19:02:42 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_traceroute.h"

bool receivePacket(int sockFd, struct timeval sendTime, char *destIp)
{
  int bytesReceived = 0;
  char buffer[ICMP_REPLY_LEN];
  struct icmp *icmpHeader;
  struct ip *ipHeader;
  struct timeval replyTime = {0, 0};

  bzero(&buffer, sizeof(buffer));
  bytesReceived = recvfrom(sockFd, buffer, sizeof(buffer), 0, traceroute_struct->results->ai_addr, &traceroute_struct->results->ai_addrlen);

  if (gettimeofday(&replyTime, 0))
    ft_error(1, "gettimeofday: ", true);

  if (bytesReceived > 0)
  {
    ipHeader = (struct ip *)buffer;
    icmpHeader = (struct icmp *)&buffer[IP_HEADER_SIZE];

    (void)ipHeader;
    uint16_t tmpCksum = icmpHeader->icmp_cksum;
    icmpHeader->icmp_cksum = 0;

    if (icmpHeader->icmp_type == ICMP_TIMXCEED && icmpHeader->icmp_code == ICMP_TIMXCEED_INTRANS && calcCksum(icmpHeader, sizeof(icmpHeader)) == tmpCksum)
    {
      printf("%s ", destIp);
      printf("%0.2fms ", (replyTime.tv_sec - sendTime.tv_sec) * 1000.0 + (replyTime.tv_sec - sendTime.tv_sec) / 1000.0);
      return false;
    }
    else if (icmpHeader->icmp_type == ICMP_ECHOREPLY && icmpHeader->icmp_code == ICMP_ECHOREPLY && calcCksum(icmpHeader, sizeof(icmpHeader)) == tmpCksum)
    {
      return true;
    }
  }
  return false;
}
