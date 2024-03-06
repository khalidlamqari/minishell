/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:12 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/27 08:15:28 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	set_oldpwd(char ***env, char *pwd, char *old)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", pwd);
	if (tmp == NULL)
		return (-1);
	if (ft_add_env(tmp, env) == -1)
		return (free(tmp), -1);
	(free(tmp), free(pwd));
	tmp = ft_strjoin("OLDPWD=", old);
	if (tmp == NULL)
		return (-1);
	if (ft_add_env(tmp, env) == -1)
		return (free(tmp), -1);
	(free(old), free(tmp));
	exit_saver(0);
	return (1);
}

int	ft_cd(char **args, char ***env)
{
	char	*pwd;
	char	*old;

	old = getcwd(NULL, 0);
	if (args[1] == NULL)
	{
		if (chdir(ft_getenv("HOME", *env)) != 0)
			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	}
	else
	{
		if (chdir(args[1]) != 0)
			return (ft_throw(strerror(errno), args[1], 0, 1), -1);
	}
	pwd = getcwd(NULL, 0);
	return (set_oldpwd(env, pwd, old));
}
