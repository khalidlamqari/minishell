/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:51:12 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 15:39:38 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	quotes_in_herdoc(char **limiter)
{
	int	flag;

	flag = is_quoted(*limiter);
	if (flag)
		remove_quotes2(limiter);
	return (flag);
}

static void	herdoc_handle2(int sig)
{
	(void)sig;
	exit (1);
}

void	do_heredoc(t_hdoc *hdoc, char ***env, char **limiter)
{
	t_dollar	vars;

	vars = (t_dollar){0};
	signal(SIGINT, herdoc_handle2);
	while (1)
	{
		hdoc->line = readline("heredoc> ");
		if (hdoc->line == NULL)
			break ;
		if (!hdoc->flag)
			check_dollar(&(hdoc->line), *env, 1, vars);
		if (ft_strcmp(hdoc->line, *limiter) == 0
			&& ft_strlen(*limiter) == ft_strlen(hdoc->line))
		{
			free(hdoc->line);
			break ;
		}
		write(hdoc->fd_write, hdoc->line, ft_strlen(hdoc->line));
		write(hdoc->fd_write, "\n", 1);
		free(hdoc->line);
	}
}

int	manage_herdoc(t_hdoc *hdoc, char ***env, char **limiter)
{
	int	pid;
	int	status;
	int	id;

	pid = fork();
	if (pid == -1)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	if (pid == 0)
	{
		value_saver(0);
		do_heredoc(hdoc, env, limiter);
		exit(0);
	}
	else
	{
		id = wait(&status);
		if (id == -1)
			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
		exit_saver(0);
		if (WIFEXITED(status))
			exit_saver(WEXITSTATUS(status));
		if (exit_saver(-1) == 1)
			return (-1);
	}
	return (1);
}

int	here_doc(char **limiter, t_list *head, char ***env)
{
	t_hdoc	hdoc;
	int		i;

	hdoc.flag = quotes_in_herdoc(limiter);
	if (!hdoc.flag)
		check_dollar(limiter, *env, 1, (t_dollar){0});
	hdoc.fd_write = open_handle("here_doc", 1, 0, *env);
	hdoc.fd_read = open_handle("here_doc", 0, 0, *env);
	if (unlink("here_doc") == -1)
		return (-1);
	i = manage_herdoc(&hdoc, env, limiter);
	if (!head)
	{
		if (close_handle(hdoc.fd_write, 0) == -1
			|| close_handle(hdoc.fd_read, 0) == -1)
			return (-1);
		return (i);
	}
	if (close_handle(head->hered_fd, 0) == -1
		|| close_handle(hdoc.fd_write, 0) == -1)
		return (-1);
	head->hered_fd = hdoc.fd_read;
	return (i);
}
