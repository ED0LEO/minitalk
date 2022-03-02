/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:40:05 by mlothair          #+#    #+#             */
/*   Updated: 2021/10/27 18:43:23 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) info;
	(void) context;
}

void	send_bin(int pid, char *s)
{
	int	i;

	while (*s)
	{
		i = 7;
		while (i >= 0 && *s)
		{
			usleep(220);
			if (*s & 1 << i)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i--;
			pause();
		}
		s++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;
	int					server_pid;
	char				*str;

	if (argc < 2)
		exit(1);
	server_pid = ft_atoi(argv[1]);
	str = argv[2];
	if (!server_pid || !str)
		exit(1);
	ft_memset(&sigact, 0, sizeof(sigact));
	sigemptyset(&sigact.sa_mask);
	sigact.sa_sigaction = handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	send_bin(server_pid, str);
	exit(0);
}
