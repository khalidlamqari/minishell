/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:55:11 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/01 10:48:11 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	break_or_continue(char **input)
{
	if ((*input)[0])
		add_history(*input);
	if (ft_quots_end(input) == 0)
	{
		free(*input);
		return (-1);
	}
	return (1);
}

static t_list	*loop_on_cmds_helper(t_list **head, char **cmds, int i)
{
	t_list	*new_node;

	new_node = new_cmd(cmds, i);
	if (new_node == NULL)
		return (lst_clear(*head), NULL);
	if (ft_parssing(cmds, i, new_node) == -1)
		return (free(new_node), lst_clear(*head), NULL);
	return (new_node);
}

int	loop_on_cmds(t_list **head, char **cmds)
{
	t_list	*new_node;
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (i == 0 || ft_strcmp(cmds[i], "|") == 0)
		{
			if (i > 0)
			{
				new_node = loop_on_cmds_helper(head, cmds, i + 1);
				if (new_node == NULL)
					return (-1);
			}
			else
			{
				new_node = loop_on_cmds_helper(head, cmds, i);
				if (new_node == NULL)
					return (-1);
			}
			ft_append_node(head, new_node);
		}
		i++;
	}
	return (1);
}

static int	main_parse_helper(t_list **head, char ***cmds,
	char **env, char *input)
{
	*cmds = split_args(input);
	if (*cmds == NULL)
		return (free(input), -1);
	if (check_syntax_err(*cmds, env) == -1 || input[0] == '\0')
		return (free(input), ft_free(*cmds), -1);
	if (loop_on_cmds(head, *cmds) == -1)
		return (free (input), ft_free(*cmds), -1);
	if (list_remove_quotes(*head) == -1)
		return (lst_clear(*head), free(input), ft_free(*cmds), -1);
	if (expander(*head, env) == -1)
		return (lst_clear(*head), free(input), ft_free(*cmds), -1);
	if (input)
		free(input);
	return (1);
}

int	main_parse(t_list **head, char ***cmds, char **env)
{
	char		*input;
	t_list		*new_node;
	t_dollar	d;
	int			i;

	d = (t_dollar){0};
	new_node = NULL;
	input = readline ("\033[38;5;202mminishell\033[1;32m$ \033[0m");
	if (!input)
		return (0);
	if (!env)
	{
		ft_throw("Cannot allocate memory", NULL, 0, 1);
		return (free(input), -1);
	}
	if (ft_white(input) == 0)
		return (free(input), -1);
	i = break_or_continue(&input);
	if (i != 1)
		return (i);
	input = ft_add_sep(input, d);
	if (input == NULL)
		return (-1);
	return (main_parse_helper(head, cmds, env, input));
}
