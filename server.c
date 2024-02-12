/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteinka <jsteinka@student.42Wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:42:21 by jsteinka          #+#    #+#             */
/*   Updated: 2024/02/12 14:24:55 by jsteinka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = -1;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		printf("ERROR heiyaa: can't send signal to PID : %d\n", info->si_pid);
		exit(EXIT_FAILURE);
	}
	if (bit < 0 && !c)
		printf("\nClient say : \n");
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;
	if (sig == SIGUSR1)
		c |= 1 << bit;
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		write(1, &c, 1);
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);
	bit--;
	kill(info->si_pid, SIGUSR1);
}

void	init_signal_handler(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	signalstruct;

	signalstruct.sa_sigaction = handler;
	signalstruct.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&signalstruct.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &signalstruct, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &signalstruct, 0);
}

int	main(void)
{
	init_signal_handler(SIGUSR1, &sig_usr);
	init_signal_handler(SIGUSR2, &sig_usr);
	printf("pid: %d\n", getpid());
	while (1)
		sleep(1);
}
