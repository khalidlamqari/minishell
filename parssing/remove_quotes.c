/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:06:22 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 11:11:42 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	ft_get_quote_type(char *s)
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

int	ft_first_quote(char *s, char type)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == type)
			return (i);
		i++;
	}
	return (-1);
}

void	remove_quotes2(char **str)
{
	char	type;
	int		f;

	type = ft_get_quote_type((*str));
	while (type != 0)
	{
		remove_char_from_arr(str, ft_first_quote(*str, type));
		f = ft_first_quote(*str, type);
		remove_char_from_arr(str, f);
		type = ft_get_quote_type((*str) + f);
	}
}

int	remove_quotes(char ***args)
{
	int		i;
	char	type;
	int		flag;

	i = 0;
	if (!(*args))
		return (1);
	while ((*args)[i])
	{
		flag = 0;
		if (is_redirection((*args)[i]) == 2)
			flag = 1;
		type = ft_get_quote_type((*args)[i]);
		if (type != 0)
		{
			if (remove_q(&(*args)[i]) == -1)
				return (-1);
		}
		if (flag)
			i++;
		i++;
	}
	return (1);
}
