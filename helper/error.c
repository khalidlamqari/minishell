/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:57:20 by klamqari          #+#    #+#             */
/*   Updated: 2024/02/26 16:48:34 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_throw(char *str, char *av, int ext, int exit_status)
{
	ft_putstr_fd(2, "minishell: ");
	if (av)
		ft_putstr_fd(2, av);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd_nl(2, str);
	exit_saver(exit_status);
	if (ext)
		exit(1);
}

void	ft_syntax_error(char *msg)
{
	ft_putstr_fd(2, "minishell: syntax error near unexpected token `");
	ft_putstr_fd(2, msg);
	ft_putstr_fd(2, "'\n");
}
