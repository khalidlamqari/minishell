/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:58:58 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 16:27:18 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_cmd(int err, char *path, t_list *node)
{
	if (err == 1)
	{
		ft_throw("is a directory", node->args[0], 0, 126);
		exit (126);
	}
	if (err == 2)
	{
		ft_throw("No such file or directory", path, 0, 127);
		exit (127);
	}
	if (err == 3)
	{
		ft_throw("command not found", node->args[0], 0, 127);
		exit (127);
	}
	if (err == 4)
	{
		ft_throw("Permission denied", path, 0, 126);
		exit (126);
	}
	if (err == 5)
	{
		ft_throw("Not a directory", path, 0, 126);
		exit (126);
	}
}

int	only_slashes(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_getenv(char *var_name, char **env)
{
	int	i;
	int	var_len;

	i = 0;
	if (!var_name || !(*env))
		return (NULL);
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], var_len) == 0
			&& env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}
