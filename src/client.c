/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:59:17 by akumari           #+#    #+#             */
/*   Updated: 2025/02/05 15:53:40 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	g_acknowledgment_received = 0;

int send_char_to_bit(int pid, char ch)
{
    int bit = 7;
	
    while (bit >= 0)
    {
        if ((ch >> bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
		while (!g_acknowledgment_received)
			usleep(200);
		g_acknowledgment_received = 0;
        bit--;
    }
	return (0);
}

void	signal_handle(int signo, siginfo_t *info, void *context)
{
	static int	i = 0;

	(void)info;
	(void)context;
	g_acknowledgment_received = 1;
	if (signo == SIGUSR1)
	{
		i++;
		if (i % 8 == 0)
		{
			ft_printf("Total number of bytes received: %d\n", i / 8);
		}
	}
	else if (signo == SIGUSR2)
		i++;
}

int test_pid_server_connection(int pid)
{
	if (kill(pid, 0) == -1) 
	{ 
		printf("Error: No server found with PID %d.\n", pid);
		return (0); 
    }
    return (1);
}

static int	check_valid_pid(char *argv[])
{
	int	i;
	int	pid;

	i = 0;
	while (argv[1][i] != '\0')
	{
		if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
		{
			printf("Error: PID should contain only integers.\n");
			return (-1);
		}
		i++;
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		printf("Error: PID should be a valid positive number.\n");
		return (-1);
	}
	return (pid);
}

int	main(int argc, char *argv[])
{
	struct sigaction sa;
	int pid;
	int i;

	if (argc != 3)
	{
		ft_printf("\e[33mTry: ./client <PID> <MESSAGE>\e[0m\n");
		return (1);
	}
	i = 0;
	pid = check_valid_pid(argv);
	if(pid == -1)
		return (1);
	if (!test_pid_server_connection(pid))
        return (1);
	setup_signal(&sa);
	while (argv[2][i] != '\0')
    {
        send_char_to_bit(pid, argv[2][i]);
        i++;
    }
    send_char_to_bit(pid, '\0');
	return (0);
}
