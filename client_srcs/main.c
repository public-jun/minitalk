/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:16:14 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/04 20:37:27 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "../libft/libft.h"

int	main(int argc, char **argv)
{
	int		i;
	pid_t		pid;
	char	*p_pid;

	if (argc != 3)
	{
		ft_putstr_fd("./client [server PID] [String]\n", 2);
		exit(EXIT_FAILURE);
	}
	p_pid = argv[1];
	i =  0;
	while (p_pid[i])
	{
		if (!ft_isdigit((int)p_pid[i]))
		{
			ft_putstr_fd("./client [server PID] [String]\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pid = (pid_t)ft_atoi(p_pid);
	if ((int)pid <= 1)
	{
		ft_putstr_fd("Invalid server PID\n", 2);
		exit(EXIT_FAILURE);
	}
	//killでserverに命令してみる
	if (kill(pid, SIGUSR1) < 0)
	{
		ft_putstr_fd("kill error\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
