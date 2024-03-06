/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:27:28 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/27 08:17:43 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_index_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	check_ifexist(char *str, char **env)
{
	int	n;
	int	n2;
	int	i;

	i = 0;
	n = get_index_equal(str);
	if (str[n - 1] == '+')
		n--;
	while (env[i])
	{
		n2 = get_index_equal(env[i]);
		if (n2 == n && strncmp(str, env[i], n) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_replace_env(char *str, char ***env, int ex)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL && ft_strchr((*env)[ex], '='))
		return (1);
	free((*env)[ex]);
	(*env)[ex] = ft_strdup(str);
	if ((*env)[ex] == NULL)
		return (-1);
	return (1);
}

int	ft_plus_equal(char *str, char ***env, int i)
{
	char	*new;
	char	*tmp;

	tmp = ft_substr(str, get_index_equal(str) + 1, ft_strlen(str) - 1);
	if (tmp == NULL)
		return (-1);
	new = ft_strjoin((*env)[i], tmp);
	if (new == NULL)
		return (free(tmp), -1);
	free(tmp);
	free((*env)[i]);
	(*env)[i] = new;
	return (1);
}

int	not_valid_arg(char *arg)
{
	int	i;
	int	n;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	n = get_index_equal(arg);
	while (i < n - 1)
	{
		if (!ft_isalpha(arg[i]) && arg[i] != '_' && !ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	if (!ft_isalpha(arg[n - 1]) && arg[n - 1] != '_' && arg[n - 1] != '+'
		&& !ft_isdigit(arg[n - 1]))
		return (1);
	return (0);
}
