/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:03:40 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/27 18:22:15 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	print_mess(char (*mess)[], pid_t client_pid)
{
	write(1, *mess, g_t_data.now_byte);
	write(1, "\n", 1);
	if (kill(client_pid, SIGUSR2) < 0)
	{
		ft_putstr_fd("kill error\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	print_max_buffer(char (*mess)[], t_bool_info *info)
{
	write(1, mess, BUFFER_SIZE);
	ft_memset(mess, 0b0, BUFFER_SIZE);
	g_t_data.now_byte = 0;
	info->b_byte_reset = true;
	g_t_data.tmp = *mess;
}

void	print_client_pid(char *client_pid)
{
	ft_putstr_fd("\x1b[33m", 1);
	ft_putstr_fd("[ CLIENT ProcessID: ", 1);
	ft_putstr_fd(client_pid, 1);
	ft_putstr_fd(" ]\x1b[0m", 1);
}
