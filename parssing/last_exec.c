/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:43:39 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/01 17:45:24 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	last_cmd(char ***env, int i, t_list *node, int len)
{
	char	*tmp2;

	tmp2 = ft_strdup(node->args[len - 1]);
	if (tmp2 == NULL)
		return (-1);
	if (remove_q(&tmp2) == -1)
		return (-1);
	(*env)[i] = ft_strjoin("_=", node->args[len - 1]);
	free(tmp2);
	if ((*env)[i] == NULL)
		return (-1);
	return (1);
}

static int	search_for_lastexec(t_list *node, char ***env, char *tmp, int len)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if ((*env)[i] + 2 == tmp)
		{
			free((*env)[i]);
			if (ft_lstsize(node) != 1)
			{
				(*env)[i] = ft_strjoin("_=", "");
				if ((*env)[i] == NULL)
					return (-1);
				return (1);
			}
			if (last_cmd(env, i, node, len) == -1)
				return (-1);
			return (1);
		}
		i++;
	}
	return (1);
}

int	ft_last_exec(t_list *node, char ***env)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = ft_getenv("_", *env);
	if (!tmp)
	{
		ft_add_env("_=\"\"", env);
		tmp = ft_getenv("_", *env);
	}
	while (node->args[len])
		len++;
	if (len == 0)
		return (1);
	if (search_for_lastexec(node, env, tmp, len) == -1)
		return (-1);
	return (1);
}
