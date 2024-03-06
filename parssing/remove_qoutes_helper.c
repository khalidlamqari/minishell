/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoutes_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:54:39 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/01 10:50:00 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_end_quots2(char *inp)
{
	int		i;
	int		count_qouts;
	char	type;

	type = ft_get_quots_type(inp);
	i = 0;
	count_qouts = 0;
	while (inp[i] && type != 0)
	{
		if ((size_t)i == (ft_strlen(inp)))
			return (-1);
		if (inp[i] == type)
			count_qouts++;
		if (count_qouts == 2)
			return (i);
		i++;
	}
	return (-1);
}

int	check_quots2(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == '"' || inp[i] == '\'')
			return (1);
		if (inp[i])
			i++;
	}
	return (0);
}

static int	remove_h(char **inp, int start, int end, int *i)
{
	if (end != -1 && start != -1)
	{
		if (remove_char_from_arr(inp, end) == -1
			|| remove_char_from_arr(inp, start) == -1)
			return (-1);
		*i -= 2;
	}
	return (1);
}

int	remove_q(char **inp)
{
	t_points	p;

	p.i = -1;
	while ((*inp)[++(p.i)])
	{
		p.end = -1;
		p.start = -1;
		while (((*inp)[p.i] != '\'' && (*inp)[p.i] != '\"') && (*inp)[p.i])
			p.i++;
		if ((*inp)[p.i] == '\0')
			return (1);
		p.start = p.i;
		if ((*inp)[p.i] && check_quots2(&(*inp)[p.i + 1]) == 1)
			p.end = get_end_quots2((*inp) + p.i) + p.i;
		p.i = (p.end);
		if (p.i == -1)
			return (1);
		if (remove_h(inp, p.start, p.end, &(p.i)) == -1)
			return (-1);
	}
	return (1);
}
