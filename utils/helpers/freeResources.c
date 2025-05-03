/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeResources.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:10:07 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/03 10:17:50 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_traceroute.h"

void freeResources()
{
  if (traceroute_struct)
  {
    if (traceroute_struct->socket != -1)
    {
      close(traceroute_struct->socket);
      traceroute_struct->socket = -1;
    }
    free(traceroute_struct);
    traceroute_struct = NULL;
    if (traceroute_struct->results)
    {
      freeaddrinfo(traceroute_struct->results);
      traceroute_struct->results = NULL;
    }
  }
}
