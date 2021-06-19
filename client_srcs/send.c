/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 22:04:10 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/19 18:10:17 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void	send_bit(pid_t server_pid, unsigned char byte)
{
	uint32_t	counter;

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
		usleep(100);
	}
}

static void	print_client_pid(char *client_pid)
{
	ft_putstr_fd("\x1b[33m", 1);
	ft_putstr_fd("[ CLIENT ProcessID: ", 1);
	ft_putstr_fd(client_pid, 1);
	ft_putstr_fd(" ]\x1b[0m\n", 1);
}

void	print_success_mess(char *mess)
{
	ft_putstr_fd("\x1b[32m", 1);
	ft_putstr_fd("[ SUCCESS: ", 1);
	ft_putstr_fd(mess, 1);
	ft_putstr_fd(" ]\x1b[0m\n", 1);
}

void	send_client_pid(pid_t server_pid)
{
	pid_t	pid;
	char	*client_pid;
	char	*tmp;

	pid = getpid();
	client_pid = ft_itoa((int)pid);
	if (!client_pid)
	{
		ft_putstr_fd("ft_itoa error\n", 2);
		exit(EXIT_FAILURE);
	}
	print_client_pid(client_pid);
	tmp = client_pid;
	while (*tmp)
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
		if (g_signo != SIGUSR1)
			pause();
		g_signo = 0;
		send_bit(server_pid, *str);
		str++;
		if (!*str)
		{
			if (g_signo != SIGUSR1)
				pause();
			g_signo = 0;
			send_bit(server_pid, *str);
			send_bit(server_pid, EOT);
		}
	}
}
