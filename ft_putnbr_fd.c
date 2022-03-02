/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <mlothair@student.21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:15:09 by mlothair          #+#    #+#             */
/*   Updated: 2021/10/07 15:07:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

static unsigned long	ft_abs(long long a)
{
	return (a * ((a > 0) - (a < 0)));
}

static unsigned long	reverse_num(unsigned int a, int	*length)
{
	unsigned long	new_num;

	new_num = 0;
	while (a)
	{
		new_num = new_num * 10 + (a % 10);
		a /= 10;
		(*length)++;
	}
	return (new_num);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned long	nn;
	char			c;
	int				length;

	length = 0;
	nn = ft_abs((long long) n);
	if (n == 0)
		write (fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	nn = reverse_num(nn, &length);
	while (length)
	{
		c = 48 + (nn % 10);
		write(fd, &c, 1);
		nn /= 10;
		length--;
	}
}
