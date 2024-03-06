/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:39:19 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/02 15:14:43 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_no_env(char ***new_env, int i)
{
	char	*pwd;
	char	*tmp;

	if (i > 0)
		if (remove_var(new_env, check_ifexist("OLDPWD", *new_env)) == -1)
			return (-1);
	if (ft_add_env("OLDPWD", new_env) == -1
		|| ft_add_shlvl(new_env) == -1)
		return (-1);
	else if (i == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
		tmp = ft_strjoin("PWD=", pwd);
		if (!tmp)
			return (free(pwd), -1);
		if (ft_add_env(tmp, new_env) == -1)
			return (-1);
		if (ft_add_env("_=", new_env) == -1)
			return (-1);
		free(pwd);
	}
	return (1);
}

int	set_env(char **env, char ***new_env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	*new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!*new_env)
	{
		ft_throw(strerror(errno), NULL, 0, 1);
		return (-1);
	}
	i = 0;
	while (env[i])
	{
		(*new_env)[i] = ft_strdup(env[i]);
		if (!(*new_env)[i])
		{
			ft_free(*new_env);
			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
		}
		i++;
	}
	(*new_env)[i] = NULL;
	return (ft_no_env(new_env, i));
}
