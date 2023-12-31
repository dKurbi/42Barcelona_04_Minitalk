/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:01 by laurmuss          #+#    #+#             */
/*   Updated: 2023/09/11 15:26:07 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/libft.h"
#include <signal.h>
#include <unistd.h>

char	*g_message;

void	receive_message(int sign, int *i, int *num_bit)
{
	static int	j = 0;
	static char	c = 0;

	if (sign == SIGUSR1)
		c = c | (128 >> *num_bit);
	(*num_bit)++;
	if ((*num_bit) == (sizeof(int) * 8) + 8)
	{
		g_message[j] = c;
		j++;
		(*num_bit) = sizeof(int) * 8;
		c = 0;
		if (j == *i)
		{
			g_message[j] = '\0';
			ft_printf("Received: %d bits, %d char.\n", (*i) * 8 + 32, *i);
			ft_printf("Message:\n%s\n", g_message);
			ft_printf("**********************************************\n");
			free(g_message);
			j = 0;
			*i = 0;
			*num_bit = 0;
		}
	}
}

void	print_cero(int *num_bit)
{
	ft_printf("Received: 32 bits, 0 char.\n");
	ft_printf("Message:\n");
	ft_printf("**********************************************\n");
	*num_bit = 0;
}

void	receive_bit(int sign)
{
	static int	num_bit = 0;
	static int	i = 0;

	if (num_bit < sizeof(int) * 8)
	{
		if (sign == SIGUSR1)
			i = i | (1 << num_bit);
		num_bit++;
		if (num_bit == sizeof(int) * 8)
		{
			if (i == 0)
				print_cero(&num_bit);
			else
			{
				g_message = ft_calloc(sizeof(char), i + 1);
				if (g_message == NULL)
				{
					ft_printf ("Malloc error");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	else
		receive_message (sign, &i, &num_bit);
}

int	main(void)
{
	ft_printf ("MiniTalk Server by dkurcbar\n");
	ft_printf ("The PID Server number to send message is: %d\n", getpid());
	ft_printf ("**********************************************\n");
	signal(SIGUSR1, receive_bit);
	signal(SIGUSR2, receive_bit);
	while (1)
		pause();
	return (0);
}
