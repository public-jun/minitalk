/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:18:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/27 18:22:59 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 1024
# define EOT 0x04

typedef struct s_bool_info
{
	bool	b_client_pid;
	bool	b_byte_reset;
}	t_bool_info;

typedef struct s_data
{
	char	*tmp;
	int		now_bit;
	int		now_byte;
}	t_data;

extern t_data	g_t_data;

/*
** init.c
*/
void	init_buff(char *message, char *p_client);
void	init_bool(t_bool_info *info);
void	set_sigaction(void	(*handler)(int), struct sigaction *act, int signo);
void	init_sigaction(void);
void	get_bit(int signo);

/*
** print_string.c
*/
void	print_mess(char (*mess)[], pid_t client_pid);
void	print_max_buffer(char (*mess)[], t_bool_info *info);

/*
** receive_bit.c
*/
void	process_receive_bit(char (*mess)[],
			char (*p_client)[], t_bool_info *info);

/*
** ack.c
*/
void	send_ack(t_bool_info *info, pid_t client_pid);
void	next_byte_and_reset_bit(t_bool_info *info);

#endif
