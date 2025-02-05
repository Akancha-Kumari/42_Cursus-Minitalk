/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:58:40 by akumari           #+#    #+#             */
/*   Updated: 2025/02/05 15:55:54 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	ch = 0;

	(void)context;
	if (signal == SIGUSR1)
		ch = (ch << 1) | 1;
	else if (signal == SIGUSR2)
		ch <<= 1;
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if (ch == '\0')
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
			return;
		}
		else
			ft_printf("%c", ch);
		ch = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_printf("\e[94mPID\e[0m \e[96m->\e[0m %d\n", pid);
	ft_printf("\e[90mWaiting for a message...\e[0m\n");
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
