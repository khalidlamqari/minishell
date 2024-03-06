/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:45:24 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/01 10:10:03 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	ft_get_q_type(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (s[i]);
		i++;
	}
	return (0);
}

int	is_exist(char *cmd, char c)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	remove_quotes3(char **arg)
{
	char	type;

	type = ft_get_q_type(*arg);
	if (type)
		if (remove_q(arg) == -1)
			return (-1);
	return (1);
}

int	*fill_arr(char **tmp3, t_list *node)
{
	int	*new_tab;
	int	i;
	int	n;
	int	j;

	j = 0;
	i = 0;
	new_tab = (int *)malloc(sizeof(int) * (ft_strlen2(tmp3) + 1));
	if (!new_tab)
		return (NULL);
	while (node->expended[i] != -1 && node->args[i])
	{
		n = ft_count_cmd(node->args[i]);
		if (n == 1)
			new_tab[j++] = node->expended[i];
		else
		{
			while (n-- != 0)
				new_tab[j++] = node->expended[i];
		}
		i++;
	}
	return (new_tab);
}
