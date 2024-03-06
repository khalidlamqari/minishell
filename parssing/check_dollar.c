/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:03:28 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/02 15:12:09 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_end_dollar(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (!is_alphanumeric(inp[i]))
		{
			if (i == 0)
				return (i);
			return (i);
		}
		i++;
	}
	if (inp[i] == '\0')
		return (i);
	return (-1);
}

int	replace_string(char *var, char **inp, int start, int end)
{
	int		i;
	int		j;
	char	*new_inp;

	i = -1;
	j = 0;
	new_inp = malloc((ft_strlen(var) + ft_strlen((*inp)) - (end - start) + 1));
	if (!new_inp)
		return (ft_throw(strerror(errno), NULL, 0, 1), -1);
	while (++i < start)
		new_inp[i] = (*inp)[i];
	while (var[j])
		new_inp[i++] = var[j++];
	end++;
	while ((*inp)[end])
		new_inp[i++] = (*inp)[end++];
	new_inp[i] = '\0';
	free((*inp));
	(*inp) = new_inp;
	return (1);
}

int	valid_dollar(char **input, char **env, t_dollar *vars)
{
	char	*tmp;
	char	*var;

	tmp = ft_substr((*input), vars->i + 1, vars->end);
	if (tmp == NULL)
		return (-1);
	if ((*input)[vars->i + 1] == '?')
	{
		var = ft_itoa(exit_saver(-1));
		if (var == NULL)
			return (-1);
		if (replace_string(var, input, vars->i, vars->i + 1) == -1)
			return (free(tmp), free(var), -1);
		free(var);
	}
	else
	{
		var = ft_getenv(tmp, env);
		if (!var)
			var = "";
		if (replace_string(var, input, vars->i, vars->end) == -1)
			return (free(tmp), -1);
	}
	vars->i += ft_strlen(var);
	return (free(tmp), 1);
}

int	ft_replace_vars(char **inp, char **env, t_dollar *vars)
{
	if (ft_isdigit((*inp)[vars->i + 1]) == 1)
		vars->end = vars->i + 1;
	else
		vars->end = get_end_dollar((*inp) + vars->i + 1) + vars->i;
	if (vars->end == vars->i && !vars->dq && ((*inp)[vars->i + 1] == '\''
		|| (*inp)[vars->i + 1] == '"' || (*inp)[vars->i + 1] == '$'))
	{
		if (remove_char_from_arr(inp, vars->i) == -1)
			return (-1);
		if (vars->i != 0)
			vars->i--;
	}
	else if (vars->end == vars->i && ((*inp)[vars->i + 1] != '\''
		|| (*inp)[vars->i + 1] != '"'))
		vars->i++;
	else
	{
		ft_exp(1);
		if (valid_dollar(inp, env, vars) == -1)
			return (-1);
	}
	return (1);
}

int	check_dollar(char **inp, char **env, int flag, t_dollar	vars)
{
	while ((*inp)[(vars.i)])
	{
		if (!flag && (*inp)[vars.i] == '"')
		{
			if (++(vars.dq) == 2)
				vars.dq = 0;
		}
		else if (!flag && (*inp)[vars.i] == '\'')
		{
			if (++(vars.count) == 2)
				vars.count = 0;
		}
		else if ((*inp)[vars.i] == '$' && !vars.count)
		{
			if (ft_replace_vars(inp, env, &vars) == -1)
				return (-1);
			if (vars.i != 0)
				vars.i--;
		}
		if ((*inp)[(vars.i)])
			vars.i++;
	}
	return (1);
}
