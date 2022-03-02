/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:40:05 by mlothair          #+#    #+#             */
/*   Updated: 2021/10/27 18:48:31 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

int	ft_powers(int base, int power)
{
	int	res;

	if (base == 0 && power == 0)
		return (1);
	if (base == 0)
		return (0);
	if (power == 0)
		return (1);
	res = 1;
	while (power--)
		res *= base;
	return (res);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	value;
	static int	i;
	static int	current_pid;

	(void) context;
	if (!current_pid)
		current_pid = info->si_pid;
	if (i != 0 && (current_pid != info->si_pid))
		return ;
	if (sig == SIGUSR1)
		value += 1 * ft_powers(2, 7 - i);
	if (sig == SIGUSR2)
		value += 0 * ft_powers(2, 7 - i);
	if (i == 7)
	{
		write (1, &value, 1);
		value *= 0;
		i *= 0;
		current_pid *= 0;
	}
	else
		i++;
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sigact;
	sigset_t			sigset;

	pid = getpid();
	ft_memset(&sigact, 0, sizeof(sigact));
	write(1, "PID ", 4);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigemptyset(&sigset);
	sigact.sa_sigaction = handler;
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_mask = sigset;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		usleep(1);
	exit(0);
}
