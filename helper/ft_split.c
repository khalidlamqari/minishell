/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:32:00 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/28 14:27:29 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_word(char *s, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (count);
}

static char	*ft_word(char *s, char sep)
{
	int		i;
	char	*w;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	w = (char *)malloc(sizeof(char) * (i + 1));
	if (!w)
		return (0);
	i = -1;
	while (s[++i] && s[i] != sep)
		w[i] = s[i];
	w[i] = '\0';
	return (w);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

char	**ft_split(char *s, char sep)
{
	int		i;
	char	**strs;
	int		j;

	j = 0;
	i = 0;
	strs = (char **)malloc(sizeof(char *) * (ft_count_word(s, sep) + 1));
	if (!strs)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	while (s[j])
	{
		while (s[j] == sep)
			j++;
		if (s[j])
		{
			strs[i] = ft_word(&s[j], sep);
			if (!strs[i])
				return (ft_free(strs), NULL);
			i++;
		}
		while (s[j] && s[j] != sep)
			j++;
	}
	strs[i] = 0;
	return (strs);
}
