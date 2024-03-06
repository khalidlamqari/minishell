/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:28:34 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/26 17:09:31 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(1, args[i]);
		if (args[i + 1])
			ft_putstr_fd(1, " ");
		i++;
	}
	if (!n)
		ft_putstr_fd(1, "\n");
	exit_saver(0);
	return (0);
}
