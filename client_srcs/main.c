/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:16:14 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/08 13:24:01 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "../libft/libft.h"

void	send_bit(pid_t server_pid, unsigned char byte)
{
	uint32_t counter;

	counter = 1 << 7;
	while (counter)
	{
		if (byte & counter)
		{
			if (kill(server_pid, SIGUSR1) < 0)
			{
				perror("kill");
				ft_putstr_fd("kill error\n", 2);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR2) < 0)
			{
				ft_putstr_fd("kill error\n", 2);
				exit(EXIT_FAILURE);
			}
		}
		counter >>= 1;
		usleep(600);
	}
}
// 'a'を送信してみる
void	send_string(pid_t server_pid, char *str)
{

	while (*str)
	{
		send_bit(server_pid, *str);
		str++;
	}
	send_bit(server_pid, *str);
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t		pid;
	char	*p_pid;

	if (argc != 3)
	{
		ft_putstr_fd("./client [server PID] [String]\n", 2);
		exit(EXIT_FAILURE);
	}
	p_pid = argv[1];
	i =  0;
	while (p_pid[i])
	{
		if (!ft_isdigit((int)p_pid[i]))
		{
			ft_putstr_fd("./client [server PID] [String]\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pid = (pid_t)ft_atoi(p_pid);
	if ((int)pid <= 1)
	{
		ft_putstr_fd("Invalid server PID\n", 2);
		exit(EXIT_FAILURE);
	}
	send_string(pid, argv[2]);
	//killでserverに命令してみる
	// if (kill(pid, SIGUSR1) < 0)
	// {
	// 	ft_putstr_fd("kill error\n", 2);
	// 	exit(EXIT_FAILURE);
	// }
	return (0);
}
