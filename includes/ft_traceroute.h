/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:48:28 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/12 17:31:23 by ybel-hac         ###   ########.fr       */
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
#include <signal.h>

#define DEFAULT_PROBES 3
#define ICMP_REQUEST_LEN 64
#define ICMP_REPLY_LEN 84
#define IP_HEADER_SIZE 20
#define ICMP_HEADER_SIZE 8
#define UDP_PACKET_SIZE 8
#define MAX_TTL 30
#define BASE_PORT 33434
#define DEFAULT_WAIT_TIME 5
#define INITIAL_TTL 1
#define MAX_PROBES_SIMULTANEOUS 16

typedef struct s_probe t_probe;
typedef struct s_options
{
  bool usageIsSpecified;
  int maxHops;
  int currentPort;
  int maxProbes;
  int waitTime;
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
  t_probe *probes;
  int probeCount;
  bool targetReached;
  char lastPrintedIp[INET_ADDRSTRLEN];
  int totalProbesSent;
  char dstIp[INET_ADDRSTRLEN];
} traceroute;

typedef struct s_probe
{
  struct timeval sendTime;
  struct timeval recvTime;
  char ip[INET_ADDRSTRLEN];
  int ttl;
  int port;
  int seq;
  bool lastReachedProbe;
  t_probe *next;
} t_probe;

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
void receivePacket(int sockFd);
void pinger();
char *ft_itoa(int n);
void ft_putNumber(int n);
void ft_putchar(char c);
void ft_putstr(const char *str);
void checkAndSetOptionAmount(char arg, char *value);
void printEmptyProbes(int maxTTL, int probes);
t_probe *addProbe(t_probe **head, int ttl, int port, int probeSeq);
t_probe *deleteProbe(t_probe **head, int port);
void freeProbes(t_probe **head);
void handleReceivedProbe(t_probe *head, struct timeval receiveTime, char *ip, int port, bool targetReached);
void printList(t_probe *head);
void handleTimeOutedProbes(t_probe *head);

#endif
