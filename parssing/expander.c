/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:15:46 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/02 15:15:24 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exp(int i)
{
	static int	exp = 0;

	if (i != -1)
		exp = i;
	return (exp);
}

int	expander_loop(char **arg, char **env)
{
	char	*tmp;

	tmp = ft_strdup(*arg);
	if (!tmp)
		return (-1);
	if (check_dollar(&(tmp), env, 0, (t_dollar){0}) == -1)
		return (-1);
	if (ft_exp(-1) == 1)
		remove_q(arg);
	(ft_exp(0), free(tmp));
	if (check_dollar(arg, env, 0, (t_dollar){0}) == -1)
		return (-1);
	return (1);
}

int	expander(t_list *head, char **env)
{
	int			i;

	while (head)
	{
		i = 0;
		if (ft_strcmp(head->args[0], "export") != 0)
		{
			while (head->args[i])
			{
				if (expander_loop(&(head->args[i]), env) == -1)
					return (-1);
				head->expended[i] = ft_exp(-1);
				(ft_exp(0), i++);
			}
			head->expended[i] = -1;
		}
		head = head->next;
	}
	return (1);
}
