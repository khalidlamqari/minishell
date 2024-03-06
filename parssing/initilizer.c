/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:42:50 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/27 13:13:11 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_data(t_list *head, char ***env, char **cmds, t_data *data)
{
	data->cmds = cmds;
	data->env = env;
	data->head = head;
	data->nbreak = 0;
	data->fd[0] = 3;
	data->fd[1] = 4;
	data->outfile = 1;
	data->infile = 0;
}
