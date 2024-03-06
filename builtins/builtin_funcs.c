/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:35:30 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/27 08:02:41 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *args)
{
	if (!args)
		return (0);
	if (ft_strcmp("echo", args) == 0 && ft_strlen(args) == 4)
		return (1);
	if (ft_strcmp("cd", args) == 0 && ft_strlen(args) == 2)
		return (1);
	if (ft_strcmp("pwd", args) == 0 && ft_strlen(args) == 3)
		return (1);
	if (ft_strcmp("export", args) == 0 && ft_strlen(args) == 6)
		return (1);
	if (ft_strcmp("unset", args) == 0 && ft_strlen(args) == 5)
		return (1);
	if (ft_strcmp("env", args) == 0 && ft_strlen(args) == 3)
		return (1);
	if (ft_strcmp("exit", args) == 0 && ft_strlen(args) == 4)
		return (1);
	return (0);
}

int	builtin_funcs(char **args, t_data *data)
{
	if (ft_strcmp("echo", args[0]) == 0 && ft_strlen(*args) == 4)
		ft_echo(args);
	if (ft_strcmp("cd", args[0]) == 0 && ft_strlen(*args) == 2)
		if (ft_cd(args, data->env) == -1)
			return (-1);
	if (ft_strcmp("pwd", args[0]) == 0 && ft_strlen(*args) == 3)
		if (ft_pwd() == -1)
			return (-1);
	if (ft_strcmp("export", args[0]) == 0 && ft_strlen(*args) == 6)
		if (ft_export(args, data->env) == -1)
			return (-1);
	if (ft_strcmp("unset", args[0]) == 0 && ft_strlen(*args) == 5)
		if (ft_unset(args, data->env) == -1)
			return (-1);
	if (ft_strcmp("env", args[0]) == 0 && ft_strlen(*args) == 3)
		ft_env(args, *(data->env));
	if (ft_strcmp("exit", args[0]) == 0 && ft_strlen(*args) == 4)
		ft_exit(args);
	return (1);
}
