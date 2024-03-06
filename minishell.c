/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 08:54:12 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/03 08:22:11 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_check_here_doc(int size, char **args)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp(args[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_limiter(int size, char **av)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp("<<", av[i]) == 0 && av[i + 1])
			return (av[i + 1]);
		i++;
	}
	return (NULL);
}

void	restore_terminal_attributes(struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}

void	main_loop(t_data *data, char **new_env,
	struct termios *original_termios)
{
	char			**cmds;
	int				i;
	t_list			*head;

	while (1)
	{
		if (start_or_end(1) == -1)
			return ;
		cmds = NULL;
		head = NULL;
		i = main_parse(&head, &cmds, new_env);
		if (i == 0)
			end_of_program();
		if (i == -1)
			continue ;
		value_saver(0);
		initialize_data(head, &new_env, cmds, data);
		ft_minishell(data);
		(ft_free(cmds), lst_clear(head));
		if (start_or_end(0) == -1)
			return ;
		restore_terminal_attributes(original_termios);
	}
	(ft_free (cmds), lst_clear(head));
}

int	main(int ac, char **av, char **env)
{
	t_data			data;
	static char		**new_env;
	struct termios	original_termios;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!new_env)
	{
		if (set_env(env, &new_env) == -1)
		{
			ft_free(new_env);
			new_env = NULL;
		}
	}
	get_terminal_attr(&original_termios);
	main_loop(&data, new_env, &original_termios);
	ft_free(new_env);
	if (close(3) == -1 || close(4) == -1)
		ft_throw(strerror(errno), NULL, 1, 1);
}
