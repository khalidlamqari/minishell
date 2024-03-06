/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:25 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/27 08:32:52 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_throw(strerror(errno), NULL, 0, 1);
		return (-1);
	}
	ft_putstr_fd(1, pwd);
	ft_putstr_fd(1, "\n");
	free(pwd);
	exit_saver(0);
	return (1);
}
