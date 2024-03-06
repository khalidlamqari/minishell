/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_h2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:23:00 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/27 08:31:36 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_add_exist_var(char *str, int ex, char ***env)
{
	int	n;

	n = get_index_equal(str);
	if (str[n - 1] == '+')
	{
		if (ft_plus_equal(str, env, ex) == -1)
			return (-1);
	}
	else
	{
		if (ft_replace_env(str, env, ex) == -1)
			return (-1);
	}
	return (1);
}
