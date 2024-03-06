/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:10:03 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/01 10:58:09 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_rederections(char **args, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (args[i] && ft_strcmp(args[i], "|") != 0)
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], "<<") == 0)
			count++;
		i++;
	}
	return (count * 2);
}

static int	count_args(char **args, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (args[i] && ft_strcmp(args[i], "|") != 0)
	{
		if (i == 0 && is_redirection(args[i]) == 0)
			count++;
		else if (i != 0 && is_redirection(args[i]) == 0
			&& is_redirection(args[i - 1]) == 0)
			count++;
		i++;
	}
	return (count);
}

t_list	*new_cmd(char **args, int start)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	node->args = (char **)malloc((count_args(args, start) + 1)
			* sizeof(char *));
	if (!(node->args))
		return (free(node), ft_throw(strerror(errno), NULL, 0, 1), NULL);
	node->expended = (int *)malloc((count_args(args, start) + 1) * sizeof(int));
	if (!(node->expended))
		return (free(node->args), free(node),
			ft_throw(strerror(errno), NULL, 0, 1), NULL);
	node->rederections = (char **)malloc((count_rederections(args, start) + 1)
			* sizeof(char *));
	if (!(node->rederections))
		return (free(node->args), free(node->expended), free(node),
			ft_throw(strerror(errno), NULL, 0, 1), NULL);
	node->next = NULL;
	return (node);
}

void	ft_free2(char **s)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (s[i] != NULL)
			free(s[i]);
		i++;
	}
	free(s);
}
