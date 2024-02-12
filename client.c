/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteinka <jsteinka@student.42Wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:42:17 by jsteinka          #+#    #+#             */
/*   Updated: 2024/02/12 13:40:09 by jsteinka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int	g_bit_control;

int	ft_atoi(const char *str)
{
	int	index;
	int	num;
	int	sign;

	index = 0;
	num = 0;
	sign = 1;
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == ' ')
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		num = num * 10 + str[index] - '0';
		index++;
	}
	return (num * sign);
}

void	submit_char(char c, pid_t pid)
{
	int	bit;

	bit = __CHAR_BIT__ * sizeof(c) - 1;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			printf("ERROR HEIYAA : Cant send signal to PID : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_bit_control = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_bit_control != 1)
			usleep(10);
	}
}

void	submit_str(char *str, pid_t pid)
{
	int	index;

	index = 0;
	while (str[index])
	{
		submit_char(str[index], pid);
		index++;
	}
	submit_char(0, pid);
}

void	acknowledge_message(int signal)
{
	if (signal == SIGUSR1)
		g_bit_control = 1;
	else if (signal == SIGUSR2)
	{
		printf("Fuyooo!! Message was received !\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		printf("Argument fail, heiyaa!!\n type: ./client <pid> <message>\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &acknowledge_message);
	signal(SIGUSR2, &acknowledge_message);
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		printf("Heiyaaa, %s is an invalid pid\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	submit_str(argv[2], pid);
	while (1)
		sleep(1);
}
