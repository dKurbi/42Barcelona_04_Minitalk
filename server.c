/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:01 by laurmuss          #+#    #+#             */
/*   Updated: 2023/08/30 18:57:20 by dkurcbar         ###   ########.fr       */
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
			j = 0;
			*i = 0;
			*num_bit = 0;
			ft_printf("%s\n", g_message);
			free(g_message);
		}
	}
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
			ft_printf("%d\n", i);
			g_message = ft_calloc(sizeof(char), i + 1);
		}
	}
	else
		receive_message (sign, &i, &num_bit);
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, receive_bit);
	signal(SIGUSR2, receive_bit);
	while (1)
		pause();
	return (0);
}
