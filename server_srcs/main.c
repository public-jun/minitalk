/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:58:04 by nakahodoju        #+#    #+#             */
/*   Updated: 2021/06/08 22:19:46 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "../libft/libft.h"
#define BUFFER_SIZE 1024

// void	handler(int signo)
// {
// 	ft_putstr_fd("signal SIGUSR1!!!\n", 1);
// }

char	message[BUFFER_SIZE];

int	now_bit = 0;
int	now_byte = 0;

void	init_mess(void)
{
	ft_memset(message, 0b0, BUFFER_SIZE);
}

void	action_on(int signo, siginfo_t *info, void *context)
{
	//ft_putstr_fd("sigaction SIGUSR1!!!\n", 1);
	// write(1, "1", 1);
	// message[0] |= (1 << now_bit);
	message[now_byte] <<= 1;
	message[now_byte]++;
	// printf("message:%d\n", message[0]);
	now_bit++;
	if (now_bit == 8)
	{
		now_byte++;
		now_bit = 0;
	}
}


void	action_off(int signo, siginfo_t *info, void *context)
{
	//ft_putstr_fd("sigaction SIGUSR2!!!\n", 1);
	// write(1, "0", 1);
	// message[0] &= ~(1 << now_bit);
	message[now_byte] <<= 1;
	// printf("message:%d\n", message[0]);
	now_bit++;
	if (now_bit == 8)
	{
		now_byte++;
		now_bit = 0;
	}
}

int	main(void)
{
	int					ret;
	char				*pid;
	struct sigaction	act_on;
	struct sigaction	act_off;
	sigset_t			sigset;

	init_mess();

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
	act_on.sa_sigaction = action_on;
	act_off.sa_sigaction = action_off;
	act_on.sa_mask = sigset;
	act_off.sa_mask = sigset;

	act_on.sa_flags = SA_SIGINFO;
	act_off.sa_flags = SA_SIGINFO;

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
	//system("ps | grep ./server");

	pid = ft_itoa((int)getpid());

	write(1, "SERVER PID: ", 12);
	write(1, pid, (int)ft_strlen(pid));
	write(1, "\n", 1);
	free_set(&pid, NULL);
	//system("leaks server");
	// signal(SIGUSR1, handler);
	while (1)
	{
		pause();
		//ヌル文字が送信されたら出力
		if (message[now_byte - 1] == 0 && !now_bit)
		{
			write(1, message, now_byte - 1);
			ft_memset(message, 0b0, BUFFER_SIZE);
			now_bit = 0;
			now_byte = 0;
		}
		//BUFFERがMAX時
		else if (now_byte == BUFFER_SIZE)
		{
			write(1, message, BUFFER_SIZE);
			ft_memset(message, 0b0, BUFFER_SIZE);
			now_bit = 0;
			now_byte = 0;
		}
	}
	return (0);
}
