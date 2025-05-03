/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:48:28 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/03 18:58:49 by ybel-hac         ###   ########.fr       */
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
#include <arpa/inet.h>

#define ICMP_REQUEST_LEN 64
#define ICMP_REPLY_LEN 84
#define IP_HEADER_SIZE 20
#define MAX_TTL 64

typedef struct s_options
{
  bool usageIsSpecified;
} t_options;

typedef struct s_traceroute
{
  char *host;
  int socket;
  struct icmp icmpHeader;
  t_options options;
  int ttl;
  struct addrinfo *results;
} traceroute;

#ifndef PING_STRUCT
extern traceroute *traceroute_struct;
#endif

void getDestIp(char *host, struct addrinfo **results);
void printUsage();
void ft_error_printf(int errCode, char *format, ...);
void ft_error(int code, char *msg, bool readErrno);
void freeResources();
void argumentsParser(int argc, char **args);
void initializer();
uint16_t calcCksum(struct icmp *icmpHeader, int len);
bool receivePacket(int sockFd, struct timeval sendTime, char *destIp);
struct timeval sendPacket(int sockfd, void *data, struct addrinfo *addr, int ttl);
void pinger();
#endif
