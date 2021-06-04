/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:58:04 by nakahodoju        #+#    #+#             */
/*   Updated: 2021/06/04 23:14:41 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "../libft/libft.h"

void	handler(int signo)
{
	ft_putstr_fd("signal SIGUSR1!!!\n", 1);
}

void	action(int signo, siginfo_t *info, void *context)
{
	ft_putstr_fd("sigaction SIGUSR1!!!\n", 1);
}

int	main(void)
{
	int					ret;
	char				*pid;
	struct sigaction	act;
	sigset_t			sigset;

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

	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_sigaction = action;
	act.sa_mask = sigset;

	act.sa_flags = SA_SIGINFO;

	ret = sigaction(SIGUSR1, &act, NULL);
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
	pause();
	return (0);
}
