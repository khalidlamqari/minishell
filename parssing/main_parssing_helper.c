/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parssing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:23:18 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/29 16:02:40 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_white(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (!is_white_space(inp[i]))
			return (1);
		i++;
	}
	return (0);
}

int	list_remove_quotes(t_list *head)
{
	while (head)
	{
		if (remove_quotes(&((head)->rederections)) == -1)
			return (-1);
		head = head->next;
	}
	return (1);
}

static int	init_args(char **cmds, t_list *list_node, int *index, int *i)
{
	(list_node)->rederections[(*index)] = ft_strdup(cmds[(*i)]);
	if ((list_node)->rederections[(*index)] == NULL)
		return (ft_free((list_node)->rederections),
			ft_free((list_node)->args), -1);
	(*index)++;
	(list_node)->rederections[(*index)] = ft_strdup(cmds[(*i) + 1]);
	if ((list_node)->rederections[(*index)] == NULL)
		return (ft_free((list_node)->rederections),
			ft_free((list_node)->args), -1);
	(*i)++;
	(*index)++;
	return (1);
}

int	ft_parssing(char **cmds, int i, t_list *list_node)
{
	int	index;
	int	index2;

	index = 0;
	index2 = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|") != 0)
	{
		if (is_redirection(cmds[i]) != 0)
		{
			if (init_args(cmds, list_node, &index, &i) == -1)
				return (-1);
		}
		else
		{
			(list_node)->args[(index2)] = ft_strdup(cmds[i]);
			if (((list_node)->args[(index2)]) == NULL)
				return (ft_free((list_node)->rederections),
					ft_free((list_node)->args), -1);
			index2++;
		}
		i++;
	}
	(list_node)->args[index2] = NULL;
	(list_node)->rederections[index] = NULL;
	return (1);
}
