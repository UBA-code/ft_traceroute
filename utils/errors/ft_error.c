/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:08:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/02 09:48:20 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_traceroute.h"

void ft_error(int code, char *msg, bool readErrno)
{
  if (readErrno)
  {
    char *errorMsg = strerror(errno);
    fprintf(stderr, "ft_traceroute: %s\n", errorMsg);
    free(errorMsg);
  }
  else
  {
    fprintf(stderr, "ft_traceroute: %s\n", msg);
  }
  freeResources();
  exit(code);
}
