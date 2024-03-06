/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_separator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:56:48 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/29 12:08:13 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_add(char c, char *s, int index)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = ft_strlen(s);
	tmp = (char *)malloc(sizeof(char) * (len + 2));
	if (!tmp)
		return (free(s), ft_throw(strerror(errno), NULL, 0, 1), NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (j == index)
			tmp[j] = c;
		else
			tmp[j] = s[i++];
		j++;
	}
	tmp[j] = '\0';
	free(s);
	s = NULL;
	return (tmp);
}

static int	ft_sep_red(char **s, int *i)
{
	if ((*s)[*i + 1] == (*s)[*i])
	{
		*s = ft_add(' ', *s, *i);
		if (*s == NULL)
			return (-1);
		(*i) += 2;
	}
	else if (((*s)[*i] == '>' || (*s)[*i] == '<'))
	{
		*s = ft_add(' ', *s, *i);
		if (*s == NULL)
			return (-1);
		(*i)++;
	}
	(*i)++;
	*s = ft_add(' ', *s, *i);
	if (*s == NULL)
		return (-1);
	return (1);
}

static void	ft_count_quotes(char *s, int i, t_dollar *d)
{
	if (s[i] == '\'' && d->dq == 0)
		(d->sq)++;
	if (s[i] == '"' && d->sq == 0)
		(d->dq)++;
	if ((d->sq) == 2)
		(d->sq) = 0;
	else if (d->dq == 2)
		(d->dq) = 0;
}

char	*ft_add_sep(char *s, t_dollar d)
{
	d.i = -1;
	d.dq = 0;
	d.sq = 0;
	while (s[++(d.i)])
	{
		if (s[d.i] == '\'' || s[d.i] == '"')
			ft_count_quotes(s, d.i, &d);
		else if ((s[d.i] == '>' || s[d.i] == '<') && (d.sq == 0 && d.dq == 0))
		{
			if (ft_sep_red(&s, &(d.i)) == -1)
				return (NULL);
		}
		else if ((s[d.i] == '|') && (d.sq == 0 && d.dq == 0))
		{
			s = ft_add(' ', s, d.i);
			if (s == NULL)
				return (NULL);
			d.i += 2;
			s = ft_add(' ', s, d.i);
			if (s == NULL)
				return (NULL);
		}
	}
	return (s);
}
