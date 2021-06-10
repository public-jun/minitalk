/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:58:04 by nakahodoju        #+#    #+#             */
/*   Updated: 2021/06/10 20:02:21 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/libft.h"
#define BUFFER_SIZE 1024
#define EOT 0x04


char	message[BUFFER_SIZE];
char	p_client[BUFFER_SIZE];
char	*g_tmp = NULL;
pid_t	client_pid = 0;

int	now_bit = 0;
int	now_byte = 0;
bool bool_client_pid = false;
bool bool_byte_reset = false;


void	init_buff(void)
{
	ft_memset(message, 0b0, BUFFER_SIZE);
	ft_memset(p_client, 0b0, BUFFER_SIZE);
}

void	get_client_pid(int signo)
{
	p_client[now_byte] <<= 1;
	if (signo == SIGUSR1)
		p_client[now_byte]++;
	now_bit++;
	if (now_bit == 8)
	{
		now_byte++;
		now_bit = 0;
	}
	if (!p_client[now_byte - 1] && now_byte > 0)
	{
		now_byte = 0;
		now_bit = 0;
		bool_client_pid = true;
	}
}

void	set_message(int	signo)
{
	message[now_byte] <<= 1;
	if (signo == SIGUSR1)
		message[now_byte]++;
	now_bit++;
	if (now_bit == 8)
	{
		now_byte++;
		now_bit = 0;
	}
}

void	get_bit(int signo)
{
	g_tmp[now_byte] <<= 1;
	if (signo == SIGUSR1)
		g_tmp[now_byte]++;
	now_bit++;
}


int	main(void)
{
	int					ret;
	char				*pid;
	struct sigaction	act_on;
	struct sigaction	act_off;
	sigset_t			sigset;

	init_buff();

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

	ft_memset(&act_on, 0, sizeof(struct sigaction));
	ft_memset(&act_off, 0, sizeof(struct sigaction));
	act_on.sa_handler = get_bit;
	act_off.sa_handler = get_bit;
	act_on.sa_mask = sigset;
	act_off.sa_mask = sigset;

	act_on.sa_flags |= SA_RESTART;
	act_off.sa_flags |= SA_RESTART;

	ret = sigaction(SIGUSR1, &act_on, NULL);
	if (ret < 0)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(1);
	}

	ret = sigaction(SIGUSR2, &act_off, NULL);
	if (ret < 0)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(1);
	}

	pid = ft_itoa((int)getpid());
	if (!pid)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(1);
	}

	write(1, "SERVER PID: ", 12);
	write(1, pid, (int)ft_strlen(pid));
	write(1, "\n", 1);
	free_set(&pid, NULL);

	g_tmp = p_client;
	while (1)
	{
		pause();
		if (now_bit == 8)
		{
			//clientのpidを受け取る
			if (bool_client_pid == false)
			{
				if (!p_client[now_byte])
				{
					now_byte = 0;
					bool_byte_reset = true;
					bool_client_pid = true;
					client_pid = (pid_t)ft_atoi(p_client);
					g_tmp = message;
				}
			}
			else if (message[now_byte] == EOT)
			{
				write(1, message, now_byte);
				write(1, "\n", 1);
				if (kill(client_pid, SIGUSR2) < 0)
				{
					ft_putstr_fd("kill error\n", 2);
					exit(EXIT_FAILURE);
				}
				ft_memset(message, 0b0, BUFFER_SIZE);
				ft_memset(p_client, 0b0, BUFFER_SIZE);
				now_bit = 0;
				now_byte = 0;
				client_pid = 0;
				bool_client_pid = false;
				bool_byte_reset = true;
				g_tmp = p_client;
			}
			else if (now_byte + 1 == BUFFER_SIZE)
			{
				write(1, message, BUFFER_SIZE);
				ft_memset(message, 0b0, BUFFER_SIZE);
				now_byte = 0;
				bool_byte_reset = true;
				g_tmp = message;
			}
			if (bool_byte_reset == true)
				bool_byte_reset = false;
			else
				now_byte++;
			now_bit = 0;
			if (bool_client_pid == true)
			{
				if (kill(client_pid, SIGUSR1) < 0)
				{
					ft_putstr_fd("kill error\n", 2);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	return (0);
}
