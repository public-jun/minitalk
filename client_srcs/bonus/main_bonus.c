/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:16:14 by jnakahod          #+#    #+#             */
/*   Updated: 2021/06/19 21:04:30 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client_bonus.h>

int	g_signo = 0;

void	catch_sig(int signo, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	g_signo = signo;
	return ;
}

void	ft_err_exit(char *mess)
{
	ft_putstr_fd(mess, 2);
	exit(EXIT_FAILURE);
}

void	init_sigaction(void)
{
	int					ret;
	struct sigaction	catch;
	sigset_t			sigset;

	ret = sigemptyset(&sigset);
	if (ret < 0)
		ft_err_exit("sigemptyset error\n");
	ret = sigaddset(&sigset, SIGINT);
	if (ret < 0)
		ft_err_exit("sigaddset error\n");
	ft_memset(&catch, 0, sizeof(struct sigaction));
	catch.sa_sigaction = catch_sig;
	catch.sa_mask = sigset;
	catch.sa_flags = SA_SIGINFO | SA_RESTART;
	ret = sigaction(SIGUSR2, &catch, NULL);
	if (ret < 0)
		ft_err_exit("sigaction error\n");
	ret = sigaction(SIGUSR1, &catch, NULL);
	if (ret < 0)
		ft_err_exit("sigaction error\n");
}

void	send_process(pid_t pid, char *str)
{
	init_sigaction();
	send_client_pid(pid);
	print_success_mess("Send ProcessID!!");
	send_string(pid, str);
	print_success_mess("Send String!!");
	while (1)
	{
		if (g_signo == SIGUSR2)
			break ;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;
	char	*p_pid;

	if (argc != 3)
		ft_err_exit("./client [server PID] [String]\n");
	p_pid = argv[1];
	i = 0;
	while (p_pid[i])
	{
		if (!ft_isdigit((int)p_pid[i]))
			ft_err_exit("./client [server PID] [String]\n");
		i++;
	}
	pid = (pid_t)ft_atoi(p_pid);
	if ((int)pid <= 1)
		ft_err_exit("Invalid server PID\n");
	send_process(pid, argv[2]);
	return (0);
}
