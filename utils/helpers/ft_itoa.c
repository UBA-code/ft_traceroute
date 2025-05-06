/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:02:15 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/05 11:36:18 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void ft_putnbr(int n, char *str, int *i)
{
  if (n == -2147483648)
  {
    str[++*i] = '-';
    str[++*i] = '2';
    ft_putnbr(147483648, str, i);
  }
  else if (n > 9)
  {
    ft_putnbr(n / 10, str, i);
    str[++*i] = (n % 10) + '0';
  }
  else if (n < 0)
  {
    str[++*i] = '-';
    ft_putnbr(-n, str, i);
  }
  else
  {
    str[++*i] = n + '0';
  }
}

char *ft_itoa(int n)
{
  char *str;
  int temp;
  int len;
  int i;

  temp = n;
  i = -1;
  len = 0;
  while (temp != 0)
  {
    temp /= 10;
    len++;
  }
  str = malloc(sizeof(char) * len + 2);
  if (!str)
    return (0);
  ft_putnbr(n, str, &i);
  if (n <= 0)
    str[len + 1] = '\0';
  else
    str[len] = '\0';
  return (str);
}
