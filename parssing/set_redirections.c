/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:09:47 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/03/01 10:54:44 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_outfile(int flag, t_list *node, t_data *data, int red)
{
	if (red == 3)
		data->outfile = open_handle(node->rederections[(data->i)],
				1, flag, *data->env);
	else
		data->outfile = open_handle(node->rederections[(data->i)],
				2, flag, *data->env);
	if (data->outfile == -1)
		return (-1);
	if (dup_handle(data->outfile, 1, flag) == -1)
	{
		close_handle(data->outfile, flag);
		return (-1);
	}
	if (close_handle(data->outfile, flag) == -1)
		return (-1);
	return (1);
}

int	ft_set_infile(int flag, t_list *node, t_data *data, int red)
{
	if (red == 4)
	{
		data->infile = open_handle(node->rederections[(data->i)],
				0, flag, *data->env);
		if (data->infile == -1)
			return (-1);
		if (dup_handle(data->infile, 0, flag) == -1)
		{
			close_handle (data->infile, flag);
			return (-1);
		}
		if (close_handle (data->infile, flag) == -1)
			return (-1);
	}
	else
		if (dup_handle(node->hered_fd, 0, flag) == -1)
			return (-1);
	return (1);
}
