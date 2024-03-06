/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:56:30 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 15:16:11 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	split_new_args(t_list *node, char ***tmp3)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	tmp2 = ft_strdup("");
	while (((node->args))[i])
	{
		tmp = ft_strjoin(tmp2, (node->args)[i]);
		if (!tmp)
			return (-1);
		free(tmp2);
		tmp2 = ft_strjoin(tmp, " ");
		if (!tmp2)
			return (free(tmp), -1);
		(free(tmp), i++);
	}
	if (remove_char_from_arr(&tmp2, ft_strlen(tmp2) - 1) == -1)
		return (-1);
	*tmp3 = split_args(tmp2);
	free(tmp2);
	return (1);
}

int	change_node_args(t_list *node)
{
	int		i;
	char	**tmp3;
	int		*new_tab;

	if (!(*(node->args)))
		return (-2);
	split_new_args(node, &tmp3);
	if (!tmp3)
		return (-1);
	new_tab = fill_arr(tmp3, node);
	i = 0;
	while (tmp3[i])
	{
		if (new_tab[i] == 0)
			if (remove_quotes3(&(tmp3[i])) == -1)
				return (-1);
		i++;
	}
	free(new_tab);
	ft_free(node->args);
	node->args = tmp3;
	return (1);
}

static int	is_big_num(char *value, int flag)
{
	ssize_t	n;

	n = ft_atoi(value);
	if (flag)
	{
		if ((ft_strlen(value) >= 19 && ft_strchr(value, '-') == NULL)
			|| (n <= 2147483646 && n >= 1000))
			return (1);
	}
	else
	{
		if ((n >= 2147483647 && n <= 9223372036854775807) || n < 0)
			return (1);
	}
	return (0);
}

int	ft_add_shlvl(char ***env)
{
	char	*value;
	int		n;
	char	*tmp;

	value = ft_getenv("SHLVL", *(env));
	if (!value || is_big_num(value, 1))
		return (ft_add_env("SHLVL=1", env));
	else if (ft_atoi(value) == 999)
		return (ft_add_env("SHLVL=", env));
	else if (is_big_num(value, 0))
		return (ft_add_env("SHLVL=0", env));
	n = ft_atoi(value);
	value = ft_itoa(n + 1);
	if (value == NULL)
		return (-1);
	tmp = ft_strjoin("SHLVL=", value);
	if (tmp == NULL)
		return (free(value), -1);
	free(value);
	if (ft_add_env(tmp, env) == -1)
		return (free(tmp), free(value), -1);
	free(tmp);
	return (1);
}

void	ft_exec(t_list *node, int *pipe1, t_data *data)
{
	char	*path;

	path = ft_get_path(node->args[0], node, data);
	if (path == NULL)
		return ;
	if (data->outfile == 1 && node->next != NULL)
		if (close(pipe1[0]) == -1 || dup2(pipe1[1], 1) == -1
			|| close(pipe1[1]) == -1)
			ft_throw(strerror(errno), NULL, 1, 1);
	if (is_builtin(node->args[0]))
	{
		builtin_funcs(node->args, data);
		exit (0);
	}
	else
	{
		execve(path, node->args, *(data->env));
		if (errno == 8)
			exit (0);
		exit (126);
	}
}
