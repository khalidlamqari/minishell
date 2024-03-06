/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:41:30 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 10:27:00 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signt)
{
	if (signt == SIGINT)
	{
		write(1, "\n", 1);
		if (err_herdoc(-1) == 1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		if (value_saver(-1) == 1)
		{
			exit_saver(1);
			rl_redisplay();
		}
		else
		{
			value_saver(1);
			exit_saver(130);
		}
	}
	if (signt == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
	}
}

// int	h_sig(int sig)
// {
// 	static int	interrupted = 0;

// 	if (sig != -1)
// 		interrupted = sig;
// 	return (interrupted);
// }

int	err_herdoc(int i)
{
	static int	err = 0;

	if (i != -1)
		err = i;
	return (err);
}

int	value_saver(int i)
{
	static int	empty;

	if (i != -1)
		empty = i;
	return (empty);
}

int	exit_saver(int i)
{
	static int	empty;

	if (i != -1)
		empty = i;
	return (empty);
}
