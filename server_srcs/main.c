/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:58:04 by nakahodoju        #+#    #+#             */
/*   Updated: 2021/06/11 16:40:03 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

char	*g_tmp = NULL;
int		g_now_bit = 0;
int		g_now_byte = 0;

void	get_bit(int signo)
{
	g_tmp[g_now_byte] <<= 1;
	if (signo == SIGUSR1)
		g_tmp[g_now_byte]++;
	g_now_bit++;
}

void	print_server_pid(void)
{
	char				*pid;

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
}

int	main(void)
{
	char		message[BUFFER_SIZE];
	char		p_client[BUFFER_SIZE];
	t_bool_info	bool_info;

	print_server_pid();
	init_buff(message, p_client);
	init_bool(&bool_info);
	init_sigaction();
	g_tmp = p_client;
	process_receive_bit(&message, &p_client, &bool_info);
	return (0);
}
