/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arecce <arecce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:07:30 by arecce            #+#    #+#             */
/*   Updated: 2022/06/17 17:39:30 by arecce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	num;
	int	counter;

	i = 0;
	neg = 1;
	num = 0;
	counter = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	while ((str[i] == '-' || str[i] == '+') && counter++ == 0)
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= neg;
	return (num);
}

void	msg_received(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Messaggio ricevuto\n");
	return ;
}

void	msg_tosend(int pid, char *msg)
{
	char	c;
	int		b;
	int		i;

	i = 0;
	while (msg[i])
	{
		b = 8;
		c = msg[i];
		while (b--)
		{
			if (c >> b & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;

	if (argc < 3)
		return (ft_printf("Error!\n"));
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, msg_received);
	if (argc == 3 && pid > 0)
	{
		msg = argv[2];
		msg_tosend(pid, msg);
		msg_tosend(pid, "\n");
	}
	else
		return (ft_printf("Error PID!\n"));
	return (0);
}
