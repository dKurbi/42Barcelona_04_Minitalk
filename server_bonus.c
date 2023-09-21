/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:01 by laurmuss          #+#    #+#             */
/*   Updated: 2023/09/11 15:26:53 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft/libft.h"
#include <signal.h>
#include <unistd.h>

char	*g_message;

void	sig_back(siginfo_t *sa, int sig)
{
	if (sig == SIGUSR1)
	{
		if (kill(sa->si_pid, SIGUSR1) == -1)
			ft_printf("*******\nsending answer fail\n********\n");
	}
	else
	{
		if (kill(sa->si_pid, SIGUSR2) == -1)
			ft_printf("*******\nsending answer fail\n********\n");
	}
}

static void	receive_message(int sig, int *i, siginfo_t *sa, int *num_bit)
{
	static int	j = 0;
	static char	c = 0;

	if (sig == SIGUSR1)
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
			sig_back(sa, SIGUSR2);
		}
	}
}

void	print_cero(int *num_bit, siginfo_t *sa)
{
	ft_printf("Received: 32 bits, 0 char.\n");
	ft_printf("Message:\n");
	ft_printf("**********************************************\n");
	*num_bit = 0;
	if (kill(sa->si_pid, SIGUSR2) == -1)
		ft_printf("*******\nsending answer fail\n********\n");
}

void	receive_bit(int sig, siginfo_t *sa, void *data)
{
	static int	num_bit = 0;
	static int	i = 0;

	(void) data;
	sig_back (sa, SIGUSR1);
	if (num_bit < sizeof(int) * 8)
	{
		if (sig == SIGUSR1)
			i = i | (1 << num_bit);
		num_bit++;
		if (num_bit == sizeof(int) * 8)
		{
			if (i == 0)
				print_cero(&num_bit, sa);
			else
			{
				g_message = ft_calloc(sizeof(char), i + 1);
				if (g_message == NULL)
					exit(EXIT_FAILURE);
			}
		}
	}
	else
		receive_message (sig, &i, sa, &num_bit);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = receive_bit;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	ft_printf ("MiniTalk Server Bonus by dkurcbar\n");
	ft_printf ("The PID Server number to send message is: %d\n", getpid());
	ft_printf ("**********************************************\n");
	while (1)
		pause();
	return (0);
}
