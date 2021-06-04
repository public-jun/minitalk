/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:58:04 by nakahodoju        #+#    #+#             */
/*   Updated: 2021/06/04 16:58:54 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"

int	main(void)
{
	char *pid;

	//system("ps | grep ./server");

	pid = ft_itoa((int)getpid());

	write(1, "SERVER PID: ", 12);
	write(1, pid, (int)ft_strlen(pid));
	write(1, "\n", 1);
	free_set(&pid, NULL);
	//system("leaks server");
	return (0);
}
