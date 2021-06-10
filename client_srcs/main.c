/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:16:14 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/10 11:59:58 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "../libft/libft.h"
#define EOT 0x04

int	g_signo = 0;

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

void	send_client_pid(pid_t server_pid)
{
	pid_t	pid;
	char	*client_pid;
	char	*tmp;

	pid = getpid();
	client_pid = ft_itoa((int)pid);
	tmp = client_pid;
	while(*tmp)
	{
		send_bit(server_pid, *tmp);
		tmp++;
	}
	send_bit(server_pid, *tmp);
	free(client_pid);
}

void	send_string(pid_t server_pid, char *str)
{

	while (*str)
	{
		send_bit(server_pid, *str);
		str++;
	}
	send_bit(server_pid, *str);
	send_bit(server_pid, EOT);
}

void	end_client(int signo, siginfo_t *info, void *context)
{
	g_signo = signo;
	return ;
}

void	set_sigaction(void)
{
	int			ret;
	struct sigaction	end;
	sigset_t			sigset;

	ret = sigemptyset(&sigset);
	if (ret < 0)
	{
		ft_putstr_fd("sigemptyset error\n", 2);
		exit(1);
	}

	ret = sigaddset(&sigset, SIGINT);
	if (ret < 0)
	{
		ft_putstr_fd("sigaddset error\n", 2);
		exit(1);
	}
	ft_memset(&end, 0, sizeof(struct sigaction));
	end.sa_sigaction = end_client;
	end.sa_mask = sigset;
	end.sa_flags = SA_SIGINFO | SA_RESTART;
	ret = sigaction(SIGUSR2, &end, NULL);
	if (ret < 0)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(1);
	}
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

	//sigactionをset
	int			ret;
	struct sigaction	end;
	sigset_t			sigset;

	ret = sigemptyset(&sigset);
	if (ret < 0)
	{
		ft_putstr_fd("sigemptyset error\n", 2);
		exit(1);
	}

	ret = sigaddset(&sigset, SIGINT);
	if (ret < 0)
	{
		ft_putstr_fd("sigaddset error\n", 2);
		exit(1);
	}
	ft_memset(&end, 0, sizeof(struct sigaction));
	end.sa_sigaction = end_client;
	end.sa_mask = sigset;
	end.sa_flags = SA_SIGINFO | SA_RESTART;
	ret = sigaction(SIGUSR2, &end, NULL);
	if (ret < 0)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(1);
	}

	//clietのpidをserverに送信する。
	send_client_pid(pid);
	send_string(pid, argv[2]);
	while(1)
	{
		if (g_signo == SIGUSR2)
			break;
	}
	return (0);
}
