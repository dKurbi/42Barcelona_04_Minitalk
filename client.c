/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:48:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/08/30 18:56:14 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/libft.h"
#include <stdio.h>
#include <signal.h>

void	send_binary_str(char *str, int pidserv)
{
	int	num_bit;
	int	i;

	num_bit = 0;
	i = 0;
	while (str[i])
	{
		while (num_bit < 8)
		{
			if (((str[i]) & (128 >> num_bit)) == 0)
				kill(pidserv, SIGUSR2);
			else
				kill(pidserv, SIGUSR1);
			usleep(100);
			num_bit++;
		}
		num_bit = 0;
		i++;
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
			kill(pidserv, SIGUSR2);
		}
		else
		{
			kill(pidserv, SIGUSR1);
		}
		usleep(100);
		num_bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pidserv;
	int	i;

	if (argc != 3)
		return (-1);
	pidserv = ft_atoi(argv[1]);
	i = ft_strlen(argv[2]);
	ft_printf("cantidad de bytes enviados: %d\n", i);
	send_binary_int(i, pidserv);
	send_binary_str(argv[2], pidserv);
	return (0);
}
