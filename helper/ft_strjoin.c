/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:38:21 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/01 10:18:20 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*text;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	text = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!text)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	i = 0;
	j = 0;
	while (s1[j])
		text[i++] = s1[j++];
	j = 0;
	while (s2[j])
		text[i++] = s2[j++];
	text[i] = '\0';
	return (text);
}
