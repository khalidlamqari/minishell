/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:22:45 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/02 16:27:05 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_access1(char *path, t_list *node)
{
	struct stat	sb;
	char		**tmp;

	if (only_slashes(path) || (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)))
		(exit_saver(126), error_cmd(1, path, node));
	if (access (path, X_OK) == 0)
		return (1);
	if (access (path, F_OK) == 0)
		(exit_saver(126), error_cmd(4, path, NULL));
	if (path[0] != '/')
	{
		tmp = ft_split(path, '/');
		if (stat(tmp[0], &sb) == 0 && S_ISREG(sb.st_mode)
			&& ft_strcmp(tmp[0], ".") != 0)
		{
			ft_free(tmp);
			exit_saver(126);
			error_cmd(5, path, NULL);
		}
		ft_free(tmp);
	}
	(exit_saver(127), error_cmd(2, path, NULL));
	return (0);
}

int	check_access2(char *path)
{
	if (access (path, F_OK | X_OK) == 0)
		return (1);
	free (path);
	path = NULL;
	return (0);
}

static char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
		exit(1);
	tmp2 = ft_strjoin(tmp, cmd);
	if (tmp2 == NULL)
		exit(1);
	free(tmp);
	return (tmp2);
}

void	getpath_from_env(t_list *node, t_data *data, char **path)
{
	char	**paths;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	*path = ft_getenv("PATH", *(data->env));
	if (!(*path))
		(exit_saver(127), error_cmd(2, node->args[0], node));
	paths = ft_split(*path, ':');
	if (paths == NULL)
		exit(1);
	while (paths[i])
	{
		*path = join_path(paths[i], node->args[0]);
		flag = check_access2(*path);
		if (flag)
			break ;
		i++;
	}
	ft_free(paths);
	if (flag == 0)
		error_cmd(3, *path, node);
	check_access1(*path, node);
}

char	*ft_get_path(char *cmd, t_list *node, t_data *data)
{
	char	*path;
	int		flag;

	flag = 0;
	path = NULL;
	if (!cmd)
		exit (0);
	if (cmd[0] == '\0')
	{
		exit_saver(127);
		error_cmd(3, cmd, node);
	}
	if (ft_strchr(cmd, '/') || is_builtin(cmd))
	{
		if (ft_strchr(cmd, '/'))
			check_access1(cmd, node);
		return (cmd);
	}
	else
	{
		getpath_from_env(node, data, &path);
		return (path);
	}
	return (NULL);
}
