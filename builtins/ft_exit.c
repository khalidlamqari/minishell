/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 07:59:52 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 21:00:44 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numerical(char *str)
{
	int	i;
	int	numb;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			return (0);
		i++;
	}
	numb = ft_atoi(str);
	if (numb == -1)
		return (0);
	return (1);
}

static void	ft_exit_helper(char **cmds, int i)
{
	if (i == 2)
	{
		exit_saver(ft_atoi(cmds[1]));
		exit (exit_saver(-1));
	}
	else if (i > 2)
	{
		ft_throw("too many arguments", cmds[0], 0, 1);
	}
}

void	ft_exit(char **cmds)
{
	int	i;

	i = 0;
	printf("exit\n");
	while (cmds[i])
		i++;
	if (i == 1)
	{
		exit_saver(0);
		exit(0);
	}
	if (is_numerical(cmds[1]))
		ft_exit_helper(cmds, i);
	else
	{
		exit_saver(255);
		write(2, "minishell: exit: ", 16);
		write(2, cmds[1], ft_strlen(cmds[1]));
		write(2, ": numeric argument required\n", 28);
		exit (255);
	}
}
