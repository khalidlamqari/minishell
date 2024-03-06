/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:17:51 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/01 10:55:22 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(const char *inp, int start, int end)
{
	int		len;
	char	*s;
	int		i;

	i = 0;
	len = end - start;
	s = NULL;
	s = (char *)malloc(len + 2);
	if (!s)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	while (start + i <= end)
	{
		s[i] = inp[i + start];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_quots(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == ' ')
			return (0);
		else if (inp[i] == '"' || inp[i] == '\'')
			return (1);
		if (inp[i])
			i++;
	}
	return (0);
}

char	ft_get_quots_type(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == '\"' || inp[i] == '\'')
			return (inp[i]);
		if (inp[i])
			i++;
	}
	return (0);
}

int	get_end_quots(char *inp)
{
	int		i;
	int		count_qouts;
	char	type;

	type = ft_get_quots_type(inp);
	i = 0;
	count_qouts = 0;
	while (inp[i])
	{
		if ((size_t)i == (ft_strlen(inp)) - 1)
			return (i);
		if (inp[i] == type)
			count_qouts++;
		if (count_qouts % 2 == 0 && count_qouts != 0 && inp[i] == ' ')
			return (i - 1);
		i++;
	}
	if (count_qouts % 2 == 0 && count_qouts != 0 && inp[i] == '\0')
		return (i - 1);
	return (-1);
}
