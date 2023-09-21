/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:50:30 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/09/11 14:47:28 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/libft.h"
#include <stdio.h>
#include <signal.h>

void	send_error(void)
{
	ft_printf("Comunication fail\n");
	exit(EXIT_FAILURE);
}

void	send_binary_str(char *str, int pidserv)
{
	int	num_bit;
	int	i;

	num_bit = 0;
	i = -1;
	while (str[++i])
	{
		while (num_bit < 8)
		{
			if (((str[i]) & (128 >> num_bit)) == 0)
			{
				if (kill(pidserv, SIGUSR2) == -1)
					send_error();
			}
			else
			{
				if (kill(pidserv, SIGUSR1) == -1)
					send_error();
			}
			pause();
			num_bit++;
		}
		num_bit = 0;
	}
}

void	send_binary_int(int i, int pidserv)
{
	int	num_bit;

	num_bit = 0;
	while (num_bit < sizeof(int) * 8)
	{
		if ((i & (1 << num_bit)) == 0)
		{
			if (kill(pidserv, SIGUSR2) == -1)
				send_error();
		}
		else
		{
			if (kill(pidserv, SIGUSR1) == -1)
				send_error();
		}
		pause();
		num_bit++;
	}
}

void	confirm(int sig)
{
	static long long	count_bit = 0;

	if (sig == SIGUSR1)
		count_bit++;
	else
	{
		ft_printf ("Server received: %d bits\n", count_bit);
		ft_printf ("Server printed: %d characteres\n\n", (count_bit - 32) / 8);
		exit(0);
	}
	usleep(500);
}

int	main(int argc, char **argv)
{
	int	pidserv;
	int	i;

	if (argc != 3)
		return (-1);
	pidserv = ft_atoi(argv[1]);
	if (pidserv < 100 || pidserv > 99999)
		send_error();
	i = ft_strlen(argv[2]);
	ft_printf("MiniTalk Client Bonus by dkurcbar\n");
	ft_printf("\n*********************************************************\n");
	ft_printf ("Sending: %d bits, %d characters to print\n", (i * 8 + 32), i);
	ft_printf ("Messagge sent:\n%s\n", argv[2]);
	ft_printf("***********************************************************\n");
	signal(SIGUSR1, &confirm);
	signal(SIGUSR2, &confirm);
	send_binary_int(i, pidserv);
	send_binary_str(argv[2], pidserv);
	exit (0);
}
