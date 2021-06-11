/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:31:05 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/11 16:37:48 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	init_buff(char *message, char *p_client)
{
	ft_memset(message, 0b0, BUFFER_SIZE);
	ft_memset(p_client, 0b0, BUFFER_SIZE);
}

void	init_bool(t_bool_info *info)
{
	info->b_client_pid = false;
	info->b_byte_reset = false;
}

void	set_sigaction(void	(*handler)(int), struct sigaction *act, int signo)
{
	int			ret;
	sigset_t	sigset;

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
	ft_memset(act, 0, sizeof(struct sigaction));
	act->sa_handler = handler;
	act->sa_mask = sigset;
	act->sa_flags |= SA_RESTART;
	ret = sigaction(signo, act, NULL);
	if (ret < 0)
	{
		ft_putstr_fd("sigaction error\n", 2);
		exit(1);
	}
}

void	init_sigaction(void)
{
	struct sigaction	act_on;
	struct sigaction	act_off;

	set_sigaction(get_bit, &act_on, SIGUSR1);
	set_sigaction(get_bit, &act_off, SIGUSR2);
}
