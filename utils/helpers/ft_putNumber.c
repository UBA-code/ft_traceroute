/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putNumber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:33:53 by ybel-hac          #+#    #+#             */
/*   Updated: 2025/05/05 18:51:41 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void ft_putNumber(int n)
{
  if (n == -2147483648)
  {
    ft_putchar('-');
    ft_putchar('2');
    ft_putNumber(147483648);
  }
  else if (n > 9)
  {
    ft_putNumber(n / 10);
    ft_putchar(n % 10 + '0');
  }
  else if (n < 0)
  {
    ft_putchar('-');
    n = -n;
    ft_putNumber(n);
  }
  else
    ft_putchar(n + '0');
}

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_putstr(const char *str)
{
  while (*str)
  {
    write(1, str, 1);
    str++;
  }
}
