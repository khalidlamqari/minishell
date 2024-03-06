/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:48:04 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/02 15:02:51 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_add_env_help(char *str, char ***env, char **tmp, int i)
{
	tmp[i] = ft_strdup(str);
	if (tmp[i] == NULL)
		return (-1);
	tmp[i + 1] = NULL;
	free(*env);
	*env = tmp;
	return (1);
}

int	ft_add_env(char *str, char ***env)
{
	int		i;
	int		ex;
	char	**tmp;

	i = 0;
	ex = check_ifexist(str, *env);
	if (ex != -1)
	{
		if (ft_add_exist_var(str, ex, env) == -1)
			return (-1);
		return (1);
	}
	while ((*env)[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	i = 0;
	while ((*env)[i])
	{
		tmp[i] = ((*env)[i]);
		i++;
	}
	return (ft_add_env_help(str, env, tmp, i));
}

static void	ft_print_equol(char **env, int i, int j, int *equal)
{
	if (env[i][j] == '=' && *equal != 1)
	{
		*equal = 1;
		write(1, "=\"", 2);
	}
	else
		write(1, &env[i][j], 1);
}

static void	ft_show_vars(char **env)
{
	int	i;
	int	j;
	int	equal;

	i = 0;
	while (env[i])
	{
		j = 0;
		equal = 0;
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			ft_putstr_fd(1, "declare -x ");
			while (env[i][j])
			{
				ft_print_equol(env, i, j, &equal);
				j++;
			}
			if (equal == 1)
				write(1, "\"", 1);
			write(1, "\n", 1);
		}
		i++;
	}
}

int	ft_export(char **args, char ***env)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		return (ft_show_vars(*env), 1);
	while (args[++i])
		if (check_dollar(&(args)[i], *env, 0, (t_dollar){0}) == -1)
			return (-1);
	i = 0;
	exit_saver(0);
	while (args[++i])
	{
		if (not_valid_arg(args[i]) == 0)
		{
			if (ft_add_env(args[i], env) == -1)
				return (-1);
		}
		else
		{
			ft_putstr_fd(2, "minishell: export: `");
			ft_putstr_fd(2, args[i]);
			(ft_putstr_fd(2, "': not a valid identifier\n"), exit_saver(1));
		}
	}
	return (1);
}
