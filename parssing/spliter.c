/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:50:03 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/03 07:54:18 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_end_space(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (is_white_space(inp[i]))
		{
			if (i == 0)
				return (i);
			return (i - 1);
		}
		i++;
	}
	if (inp[i] == '\0')
		return (i - 1);
	return (-1);
}

int	ft_count_cmd(char *inp)
{
	t_points	p;

	p.i = 0;
	p.j = 0;
	if (!inp && !*inp)
		return (0);
	while (inp[p.i])
	{
		while (is_white_space(inp[p.i]))
			p.i++;
		if (!inp[p.i])
			break ;
		p.start = p.i;
		if (check_quots(inp + p.i) == 1 && inp[p.i])
		{
			p.end = get_end_quots(inp + p.i) + p.i;
		}
		else if (check_quots(&inp[p.i]) == 0 && inp[p.i])
			p.end = get_end_space(&inp[p.i]) + p.i;
		p.i = (p.end);
		p.j++;
		p.i++;
	}
	return (p.j);
}

static char	**ft_allocation(char *inp, t_points *p)
{
	char	**strs;
	int		count;

	if (!inp)
		return (NULL);
	count = ft_count_cmd(inp);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	p->i = 0;
	p->j = 0;
	return (strs);
}

char	**split_args(char *inp)
{
	t_points	p;
	char		**strs;

	strs = ft_allocation(inp, &p);
	if (strs == NULL)
		return (NULL);
	while (inp[p.i])
	{
		while (is_white_space(inp[p.i]))
			p.i++;
		if (!inp[p.i])
			break ;
		p.start = p.i;
		if (check_quots(inp + p.i) == 1 && inp[p.i])
			p.end = get_end_quots(inp + p.i) + p.i;
		else if (check_quots(&inp[p.i]) == 0 && inp[p.i])
			p.end = get_end_space(&inp[p.i]) + p.i;
		p.i = (p.end);
		strs[p.j] = ft_substr(inp, p.start, p.end);
		if (strs[p.j++] == NULL)
			return (ft_free(strs), NULL);
		p.i++;
	}
	strs[p.j] = 0;
	return (strs);
}
