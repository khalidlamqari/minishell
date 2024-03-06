/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:37:30 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 15:06:24 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	manage_inout_file(t_list *node, t_data *data, int flag)
{
	int	red;

	data->i = 0;
	while (node->rederections[data->i])
	{
		red = is_redirection(node->rederections[data->i]);
		if (red == 1 || red == 3)
		{
			(data->i)++;
			if (ft_set_outfile(flag, node, data, red) == -1)
				return (-1);
		}
		else if (red == 2 || red == 4)
		{
			(data->i)++;
			if (ft_set_infile(flag, node, data, red) == -1)
				return (-1);
		}
		(data->i)++;
	}
	return (1);
}

int	manage_processes(t_list *node, int *l_pid, t_data *data)
{
	pid_t	pid;
	int		pipe1[2];

	if (pipe(pipe1) == -1)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	pid = fork();
	if (pid == -1)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	*l_pid = pid;
	if (pid == 0)
	{
		signal(SIGQUIT, sigint_handler);
		value_saver(0);
		if (manage_inout_file(node, data, 1) == -1)
			exit(1);
		ft_exec(node, pipe1, data);
	}
	else
	{
		if (close_handle (pipe1[1], 0) == -1
			|| dup_handle(pipe1[0], 0, 0) == -1
			|| close_handle(pipe1[0], 0) == -1)
			return (-1);
	}
	return (1);
}

void	wait_func(int lpid, int nwait)
{
	int	status;
	int	j;
	int	wpid;

	j = 0;
	while (j < nwait)
	{
		wpid = wait(&status);
		if (wpid == lpid)
			exit_saver(WEXITSTATUS(status));
		else if (wpid == -1)
			ft_throw(strerror(errno), NULL, 0, 1);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 3)
			{
				exit_saver(131);
				write(2, "Quit: 3\n", 8);
			}
			else if (WTERMSIG(status) == 2)
				exit_saver(130);
		}
		j++;
	}
}

static int	loop_on_cmds(t_list *node, t_data *data, int *lpid, int *nwait)
{
	int	flag;

	flag = 0;
	while (node)
	{
		if (change_node_args(node) == -1)
			break ;
		if (is_builtin(node->args[0]) && ft_lstsize(data->head) == 1)
		{
			flag = 1;
			if (manage_inout_file(node, data, 0) == -1)
				break ;
			builtin_funcs(node->args, data);
			break ;
		}
		if (manage_processes(node, lpid, data) == -1)
			break ;
		if (node->hered_fd != -1)
			if (close_handle(node->hered_fd, 0) == -1)
				break ;
		(*nwait)++;
		node = node->next;
	}
	return (flag);
}

void	ft_minishell(t_data *data)
{
	t_list	*node;
	int		lpid;
	int		flag;
	int		nwait;

	nwait = 0;
	flag = 0;
	node = data->head;
	if (ft_last_exec(data->head, data->env) == -1)
		return ;
	if (get_last_here_doc(data->head, data->env) == -1)
		return ;
	flag = loop_on_cmds(node, data, &lpid, &nwait);
	if (flag == 0)
		wait_func(lpid, nwait);
}
