/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:38:58 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/25 09:45:44 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cout_char(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (c == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	ft_get_first_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (s[i]);
		i++;
	}
	return (0);
}

int	get_index_of_next(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		if (count == 2)
			return (i);
		i++;
	}
	return (0);
}

int	ft_quots_end(char **input)
{
	char	first;
	int		i;
	int		qout;
	char	f;

	i = -1;
	while ((*input)[++i])
	{
		f = 0;
		f = ft_get_first_char((*input) + i);
		if (f != 0)
			first = f;
		else if (f == 0)
			break ;
		qout = get_index_of_next((*input) + i, first);
		i += qout;
		if (qout == 0)
			break ;
	}
	if (qout == 0 && first != 0)
	{
		ft_syntax_error("\"");
		return (0);
	}
	return (1);
}
