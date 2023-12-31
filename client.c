/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:48:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/09/11 14:59:09 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/libft.h"
#include <stdio.h>
#include <signal.h>

int	send_binary_str(char *str, int pidserv)
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
					return (-1);
			}
			else
			{
				if (kill(pidserv, SIGUSR1) == -1)
					return (-1);
			}
			usleep(100);
			num_bit++;
		}
		num_bit = 0;
	}
	return (0);
}

int	send_binary_int(int i, int pidserv)
{
	int	num_bit;

	num_bit = 0;
	while (num_bit < sizeof(int) * 8)
	{
		if ((i & (1 << num_bit)) == 0)
		{
			if (kill(pidserv, SIGUSR2) == -1)
				return (-1);
		}
		else
		{
			if (kill(pidserv, SIGUSR1) == -1)
				return (-1);
		}
		usleep(100);
		num_bit++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pidserv;
	int	i;

	if (argc != 3)
		return (-1);
	pidserv = ft_atoi(argv[1]);
	i = ft_strlen(argv[2]);
	ft_printf("\nMiniTalk Client by dkurcbar\n");
	ft_printf("*********************************************************\n");
	ft_printf ("Sending: %d bits, %d characters to print\n", (i * 8 + 32), i);
	ft_printf ("Messagge sent:\n%s\n", argv[2]);
	ft_printf("***********************************************************\n");
	if (send_binary_int(i, pidserv) == -1)
		return (1);
	if (send_binary_str(argv[2], pidserv) == -1)
		return (1);
	return (0);
}
