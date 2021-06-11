/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 22:06:27 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/11 16:42:51 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"

# define EOT 0x04

extern int	g_signo;

void	send_bit(pid_t server_pid, unsigned char byte);
void	send_client_pid(pid_t server_pid);
void	send_string(pid_t server_pid, char *str);
#endif