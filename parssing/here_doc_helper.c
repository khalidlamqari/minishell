/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:47:17 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/27 12:56:31 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_last_here_doc(t_list *head, char ***env)
{
	int		i;
	t_list	*tmp;
	char	*her;

	tmp = head;
	while (tmp)
	{
		i = 0;
		tmp->hered_fd = -1;
		while (tmp->rederections[i])
		{
			if (is_redirection(tmp->rederections[i]) == 2)
			{
				her = ft_strdup(tmp->rederections[++i]);
				if (her == NULL || here_doc(&her, tmp, env) == -1)
					return (free(her), -1);
				free(her);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	is_quoted(char *str)
{
	int	i;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == '\'')
				squote++;
			else
				dquote++;
		}
		if (squote == 2 || dquote == 2)
			return (1);
		i++;
	}
	return (0);
}
