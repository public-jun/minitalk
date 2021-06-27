/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ack.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:10:12 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/27 18:19:09 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	send_ack(t_bool_info *info, pid_t client_pid)
{
	if (info->b_client_pid == true)
	{
		if (kill(client_pid, SIGUSR1) < 0)
		{
			ft_putstr_fd("kill error\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	next_byte_and_reset_bit(t_bool_info *info)
{
	if (info->b_byte_reset == true)
		info->b_byte_reset = false;
	else
		g_t_data.now_byte++;
	g_t_data.now_bit = 0;
}
