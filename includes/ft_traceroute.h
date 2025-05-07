/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:48:28 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/07 09:33:11 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
#define FT_TRACEROUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/udp.h>

#define ICMP_REQUEST_LEN 64
#define ICMP_REPLY_LEN 84
#define IP_HEADER_SIZE 20
#define UDP_PACKET_SIZE 8
#define MAX_TTL 64
#define BASE_PORT 33434

typedef struct s_options
{
  bool usageIsSpecified;
} t_options;

typedef struct s_traceroute
{
  char *host;
  int sendSocket;
  int receiveSocket;
  struct icmp icmpHeader;
  struct ip ipHeader;
  t_options options;
  int ttl;
  struct addrinfo *results;
  int currentPort;
} traceroute;

#ifndef PING_STRUCT
extern traceroute *traceroute_struct;
#endif

void resolveHostName(char *host, struct addrinfo **results, const char *type);
void printUsage();
void ft_error_printf(int errCode, char *format, ...);
void ft_error(int code, char *msg, bool readErrno);
void freeResources();
void argumentsParser(int argc, char **args);
void initializer();
uint16_t calcCksum(void *icmpHeader, int len);
struct timeval sendPacket(int sockfd, struct addrinfo *addr, int ttl);
bool receivePacket(int sockFd, struct timeval sendTime, bool *isHopIpAlreadyPrinted);
void pinger();
char *ft_itoa(int n);
void ft_putNumber(int n);
void ft_putchar(char c);
void ft_putstr(const char *str);

#endif
