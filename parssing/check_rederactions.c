/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rederactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:43:44 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 10:29:11 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_herdoc(char **av, int index, char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (i < index - 1)
	{
		if (is_redirection(av[i]) == 2)
		{
			str = ft_strdup(av[i + 1]);
			err_herdoc(0);
			if (here_doc(&str, NULL, &env) == -1)
			{
				free(str);
				exit_saver(1);
				err_herdoc(1);
				return (-1);
			}
			err_herdoc(1);
			free(str);
		}
		i++;
	}
	return (1);
}

int	ft_strlen2(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_pipe_err(char **av, int index, int flag)
{
	int	i;

	i = 0;
	if (!av || !av[0])
		return (-1);
	if (ft_strcmp(av[0], "|") == 0)
		return (0);
	if (ft_strcmp(av[ft_strlen2(av) - 1], "|") == 0 && flag == 1)
		return (ft_strlen2(av) - 1);
	while (av[i])
	{
		if (ft_strcmp(av[i], "|") == 0 && ft_strcmp(av[i + 1], "|") == 0)
		{
			if (index == -1)
				return (i);
			else if (i > index)
				return (index);
			return (i);
		}
		i++;
	}
	return (index);
}

static int	handl_syntax_error(int flag, int index, char **av, char **env)
{
	if (flag != 1 || index != -1)
	{
		if (flag == -1)
		{
			if (index > 0)
			{
				if (check_herdoc(av, index, env) == -1)
					return (-1);
			}
			ft_syntax_error("newline");
			exit_saver(258);
		}
		else
		{
			ft_syntax_error(av[index]);
			if (check_herdoc(av, index, env) == -1)
				return (-1);
			exit_saver(258);
		}
		return (-1);
	}
	return (1);
}

int	check_syntax_err(char **av, char **env)
{
	int	index;
	int	flag;

	flag = 1;
	index = ft_check_red(av, &flag);
	index = check_pipe_err(av, index, flag);
	if (handl_syntax_error(flag, index, av, env) == -1)
		return (-1);
	return (1);
}
