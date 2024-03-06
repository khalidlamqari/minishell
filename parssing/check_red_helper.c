/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:38:16 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/25 08:44:44 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">>") == 0 && ft_strlen(str) == 2)
		return (1);
	if (ft_strcmp(str, "<<") == 0 && ft_strlen(str) == 2)
		return (2);
	if (ft_strcmp(str, ">") == 0 && ft_strlen(str) == 1)
		return (3);
	if (ft_strcmp(str, "<") == 0 && ft_strlen(str) == 1)
		return (4);
	return (0);
}

static void	set_status(int *status, int n)
{
	*status = n;
}

int	ft_check_red(char **av, int *status)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_redirection(av[i]) != 0 && av[i + 1] == 0)
			return (set_status(status, -1), i + 1);
		else if ((is_redirection(av[i]) == 1 && is_redirection(av[i + 1]))
			|| (is_redirection(av[i]) == 1 && ft_strcmp(av[i + 1], "|") == 0))
			return (set_status(status, 0), i + 1);
		else if ((is_redirection(av[i]) == 3 && is_redirection(av[i + 1]))
			|| (is_redirection(av[i]) == 3 && ft_strcmp(av[i + 1], "|") == 0))
			return (set_status(status, 0), i + 1);
		else if (is_redirection(av[i]) != 0 && av[i + 1] == 0)
			return (set_status(status, -1), i + 1);
		else if ((is_redirection(av[i]) == 4 && is_redirection(av[i + 1]))
			|| (is_redirection(av[i]) == 4 && ft_strcmp(av[i + 1], "|") == 0))
			return (set_status(status, 0), i + 1);
		else if ((is_redirection(av[i]) == 2 && is_redirection(av[i + 1]))
			|| (is_redirection(av[i]) == 2 && ft_strcmp(av[i + 1], "|") == 0))
			return (set_status(status, 0), i + 1);
		i++;
	}
	return (-1);
}
