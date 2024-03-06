/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:48:32 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/29 21:46:14 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	valid_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			if (cmds[i][0] == '=')
			{
				ft_throw("Invalid argument", cmds[i], 0, 1);
				return (0);
			}
		}
		else
		{
			ft_throw("No such file or directory", cmds[i], 0, 1);
			return (0);
		}
		i++;
	}
	exit_saver(0);
	return (1);
}

void	ft_env(char **cmds, char **env)
{
	int	i;
	int	flag;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	flag = valid_cmds(cmds + 1);
	if (!flag)
		return ;
	i = 1;
	while (cmds[i] && flag)
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	exit_saver(0);
}
