/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:14:18 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 13:53:56 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	int		j;
	char	*d;

	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	d = (char *)malloc((i + 1) * sizeof(char));
	if (!d)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	while (j < i)
	{
		d[j] = s1[j];
		j++;
	}
	d[j] = '\0';
	return (d);
}
