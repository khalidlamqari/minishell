/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char_from_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:23:52 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/27 11:50:07 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_char_from_arr(char **arr, int index)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(ft_strlen(*arr));
	if (!tmp)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	while ((*arr)[i])
	{
		if (i != index)
		{
			tmp[j] = (*arr)[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	free(*arr);
	*arr = tmp;
	return (1);
}
