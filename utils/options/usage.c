/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:05:50 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/13 15:13:16 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

//* Print usage and exit
void printUsage()
{
  printf("Usage: ft_traceroute [OPTION...] HOST\n");
  printf("Print the route packets trace to network host.\n");
  printf("\n");
  printf("-d\Enable socket level debugging\n");
  printf("-f\tset initial hop distance, i.e., time-to-live\n");
  printf("-m\tset maximal hop count (default: %d)\n", MAX_TTL);
  printf("-p\tuse destination PORT port (default: %d)\n", BASE_PORT);
  printf("-q\tsend NUM probe packets per hop (default: %d)\n", DEFAULT_PROBES);
  printf("-w\twait NUM seconds for response (default: %d)\n", DEFAULT_WAIT_TIME);
  // printf("-q\tquiet output\n");
  // printf("\n");
  printf("-?, --help\tgive this help list\n");
  freeResources();
  exit(0);
}

// Usage: traceroute [OPTION...] HOST
// Print the route packets trace to network host.

//   -f, --first-hop=NUM        set initial hop distance, i.e., time-to-live
//   -g, --gateways=GATES       list of gateways for loose source routing
//   -I, --icmp                 use ICMP ECHO as probe
//   -m, --max-hop=NUM          set maximal hop count (default: 64)
//   -M, --type=METHOD          use METHOD (`icmp' or `udp') for traceroute
//                              operations, defaulting to `udp'
//   -p, --port=PORT            use destination PORT port (default: 33434)
//   -q, --tries=NUM            send NUM probe packets per hop (default: 3)
//       --resolve-hostnames    resolve hostnames
//   -t, --tos=NUM              set type of service (TOS) to NUM
//   -w, --wait=NUM             wait NUM seconds for response (default: 3)
//   -?, --help                 give this help list
//       --usage                give a short usage message
//   -V, --version              print program version

// Mandatory or optional arguments to long options are also mandatory or optional
// for any corresponding short options.

// Report bugs to <bug-inetutils@gnu.org>.
