/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:28:27 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/02 15:16:43 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_white_spaces(char **str)
{
	int		i;
	char	**tmp;

	i = ft_count_word(*str, ' ');
	if (i > 1)
		return (1);
	tmp = ft_split(*str, ' ');
	if (!tmp)
		return (-1);
	free(*str);
	*str = ft_strdup(tmp[0]);
	if (!*str)
		return (ft_free(tmp), -1);
	ft_free(tmp);
	return (0);
}

static char	*check_ambiguous(char **file, char **env)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if (ft_strchr(*file, '$'))
	{
		tmp = ft_strdup(*file);
		if (!tmp)
			return (NULL);
		if (check_dollar(&tmp, env, 0, ((t_dollar){0})) == -1)
			return (free(tmp), NULL);
		i = check_white_spaces(&tmp);
		if (i == -1)
			return (free(tmp), NULL);
		if ((i == 1 || tmp[0] == '\0'))
			return (free (tmp), ft_throw("ambiguous redirect", *file, 0, 1),
				NULL);
		if (tmp)
		{
			free(*file);
			*file = tmp;
		}
		return (tmp);
	}
	return (*file);
}

int	close_handle(int fd, int ext)
{
	if (fd != -1 && close(fd) == -1)
		return (ft_throw(strerror(errno), NULL, ext, 1), -1);
	return (1);
}

int	dup_handle(int old, int new, int ext)
{
	if (dup2(old, new) == -1)
		return (ft_throw(strerror(errno), NULL, ext, 1), -1);
	return (1);
}

int	open_handle(char *file, int flag, int ext, char **env)
{
	int	fd;

	if (check_ambiguous(&file, env) == NULL)
		return (-1);
	if (flag == 0)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd < 0)
			ft_throw(strerror(errno), file, ext, 1);
		return (fd);
	}
	else if (flag == 1)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			ft_throw(strerror(errno), file, ext, 1);
		return (fd);
	}
	else
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			ft_throw(strerror(errno), file, ext, 1);
		return (fd);
	}
}
