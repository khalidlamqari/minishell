/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:48:20 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/27 08:49:52 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_arg(char *arg)
{
	int	i;
	int	n;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	n = ft_strlen(arg);
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]) && arg[i] != '_' && !ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	remove_var(char ***env, int ex)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	if (ex < 0)
		return (1);
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	if (!new_env)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (i != ex)
			new_env[j++] = (*env)[i];
		else
			free((*env)[i]);
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (1);
}

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	ex;

	i = 1;
	exit_saver(0);
	while (args[i])
	{
		if (!is_valid_arg(args[i]))
		{
			ft_putstr_fd(1, "minishell: unset: `");
			(ft_putstr_fd(1, args[i]), exit_saver(1));
			ft_putstr_fd(1, "': not a valid identifier\n");
		}
		else
		{
			ex = check_ifexist(args[i], *env);
			if (ex != -1)
			{
				if (remove_var(env, ex) == -1)
					return (-1);
			}
		}
		i++;
	}
	return (1);
}
