/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:17:15 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/03 08:22:44 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	duper(int flag)
{
	if (flag)
	{
		if (dup2(0, 3) == -1 || dup2(1, 4) == -1)
			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	}
	else
	{
		if (dup2(4, 1) == -1 || dup2(3, 0) == -1)
			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	}
	return (1);
}

void	get_terminal_attr(struct termios *original_termios)
{
	tcgetattr(STDIN_FILENO, original_termios);
	original_termios->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}

int	start_or_end(int flag)
{
	if (flag)
	{
		err_herdoc(1);
		if (duper(1) == -1)
			return (-1);
		value_saver(1);
	}
	else
		if (duper(0) == -1)
			return (-1);
	return (1);
}

void	end_of_program(void)
{
	printf("exit\n");
	exit(exit_saver(-1));
}
