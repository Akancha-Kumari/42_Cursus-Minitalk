/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:58:29 by akumari           #+#    #+#             */
/*   Updated: 2025/02/05 15:42:18 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _GNU_SOURCE
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include "../ft_printf/ft_printf.h"

int	ft_atoi(const char *str);
void	signal_handle(int signo, siginfo_t *info, void *context);
void setup_signal(struct sigaction *sa);

#endif
