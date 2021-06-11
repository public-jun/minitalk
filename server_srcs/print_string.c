/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:03:40 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/11 16:40:37 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

static pid_t	get_client_pid(t_bool_info *info,
					char (*p_client)[], char (*message)[])
{
	pid_t	client_pid;

	g_now_byte = 0;
	info->b_byte_reset = true;
	info->b_client_pid = true;
	client_pid = (pid_t)ft_atoi(*p_client);
	g_tmp = *message;
	return (client_pid);
}

static void	print_mess(char (*mess)[], pid_t client_pid)
{
	write(1, *mess, g_now_byte);
	write(1, "\n", 1);
	if (kill(client_pid, SIGUSR2) < 0)
	{
		ft_putstr_fd("kill error\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	reset_buff(char (*mess)[],
				char (*p_client)[], pid_t *client_pid, t_bool_info *info)
{
	ft_memset(*mess, 0b0, BUFFER_SIZE);
	ft_memset(*p_client, 0b0, BUFFER_SIZE);
	g_now_bit = 0;
	g_now_byte = 0;
	*client_pid = 0;
	info->b_client_pid = false;
	info->b_byte_reset = true;
	g_tmp = *p_client;
}

static void	print_max_buffer(char (*mess)[], t_bool_info *info)
{
	write(1, mess, BUFFER_SIZE);
	ft_memset(mess, 0b0, BUFFER_SIZE);
	g_now_byte = 0;
	info->b_byte_reset = true;
	g_tmp = *mess;
}

void	process_receive_bit(char (*mess)[],
			char (*p_client)[], t_bool_info *info)
{
	pid_t	client_pid;

	client_pid = 0;
	while (1)
	{
		pause();
		if (g_now_bit == 8)
		{
			if (info->b_client_pid == false && !(*p_client)[g_now_byte])
				client_pid = get_client_pid(info, p_client, mess);
			else if ((*mess)[g_now_byte] == EOT)
			{
				print_mess(mess, client_pid);
				reset_buff(mess, p_client, &client_pid, info);
			}
			else if (g_now_byte + 1 == BUFFER_SIZE)
				print_max_buffer(mess, info);
			next_byte_and_reset_bit(info);
			send_ack(info, client_pid);
		}
	}
}