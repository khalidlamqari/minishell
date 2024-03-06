/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ouad <zel-ouad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 08:54:47 by klamqari          #+#    #+#             */
/*   Updated: 2024/03/03 08:10:34 by zel-ouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libc.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>

typedef struct s_list
{
	char			**args;
	int				*expended;
	char			**rederections;
	int				fd[2];
	int				hered_fd;
	struct s_list	*next;
}					t_list;

typedef struct s_points
{
	int	i;
	int	j;
	int	start;
	int	end;
}	t_points;

typedef struct s_dollar
{
	int		i;
	int		count;
	int		dq;
	int		sq;
	int		end;
	char	*var;
	char	*tmp;
}			t_dollar;

typedef struct s_data
{
	char	**cmds;
	char	***env;
	t_list	*head;
	int		nbreak;
	int		fd[2];
	int		outfile;
	int		infile;
	int		i;
}			t_data;

typedef struct s_hdoc
{
	char	*line;
	int		fd_write;
	int		fd_read;
	int		flag;
}			t_hdoc;
int		ft_exp(int i);
//		HELPERS
int		ft_count_cmd(char *inp);
size_t	ft_strlen(char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int n);
int		ft_putstr_fd(int fd, char *s);
int		ft_putstr_fd_nl(int fd, char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_itoa(int n);
char	*ft_strchr(char *s, int c);
ssize_t	ft_atoi(const char *str);
int		ft_lstsize(t_list *lst);
char	**ft_split(char *s, char sep);
int		ft_count_word(char *s, char sep);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
void	lst_clear(t_list *lst);
void	ft_free(char **s);
void	ft_append_node(t_list **lst, t_list *new);
t_list	*new_cmd(char **args, int start);

//		PARSSING

void	initialize_data(t_list *head, char ***env, char **cmds, t_data *data);
int		here_doc(char **limiter, t_list *head, char ***env);
int		is_redirection(char *str);
int		ft_check_red(char **av, int *status);
void	ft_minishell(t_data *data);
int		ft_quots_end(char **input);
int		main_parse(t_list **head, char ***cmds, char **env);
char	*ft_add_sep(char *s, t_dollar d);
char	*ft_get_path(char *cmd, t_list *node, t_data *data);
char	**split_args(char *inp);
int		check_quots(char *inp);
char	ft_get_quots_type(char *inp);
int		get_end_quots(char *inp);
int		is_white_space(char c);
int		check_dollar(char **inp, char **env, int flag, t_dollar	vars);
char	*ft_substr(const char *inp, int start, int end);
int		get_end_space(char *inp);
int		remove_quotes(char ***args);
void	remove_quotes2(char **str);
int		remove_char_from_arr(char **arr, int index);
int		set_env(char **env, char ***new_env);
int		get_last_here_doc(t_list *head, char ***env);
int		ft_set_infile(int flag, t_list *node, t_data *data, int red);
int		ft_set_outfile(int flag, t_list *node, t_data *data, int red);
int		check_syntax_err(char **av, char **env);
int		is_quoted(char *str);
int		get_index_equal(char *str);
int		ft_parssing(char **cmds, int i, t_list *list_node);
int		list_remove_quotes(t_list *head);
int		ft_white(char *inp);
int		ft_last_exec(t_list *node, char ***env);
int		check_ifexist(char *str, char **env);
void	error_cmd(int err, char *path, t_list *node );
int		only_slashes(char *path);
void	ft_syntax_error(char *msg);
void	ft_throw(char *str, char *av, int ext, int exit_status);
char	ft_get_first_char(char *s);

// 		EXEC

int		close_handle(int fd, int ext);
int		dup_handle(int old, int new, int ext);
int		open_handle(char *file, int flag, int ext, char **env);
int		is_exist(char *cmd, char c);
void	ft_exec(t_list *node, int *pipe1, t_data *data);

//		BUILTIN

int		remove_var(char ***env, int ex);
int		ft_plus_equal(char *str, char ***env, int i);
int		is_builtin(char *args);
int		builtin_funcs(char **args, t_data *data);
int		ft_echo(char **args);
int		ft_cd(char **args, char ***env);
int		ft_pwd(void);
void	ft_env(char **cmds, char **env);
int		ft_replace_env(char *str, char ***env, int ex);
int		ft_export(char **args, char ***env);
int		ft_add_exist_var(char *str, int ex, char ***env);
int		ft_unset(char **args, char ***env);
void	ft_exit(char **cmds);
int		ft_add_env(char *str, char ***env);
int		not_valid_arg(char *arg);
int		ft_isdigit(int n);
int		ft_isalpha(int c);
int		get_index_equal(char *str);
char	*ft_getenv(char *var_name, char **env);

//    SIGNALS

void	sigint_handler(int signt);
int		h_sig(int sig);
int		err_herdoc(int i);
int		value_saver(int i);
int		exit_saver(int i);

int		change_node_args(t_list *node);
int		remove_q(char **inp);
char	*ft_add(char c, char *s, int index);
int		is_alphanumeric(char c);
int		ft_strlen2(char **s);

int		ft_add_shlvl(char ***env);
int		remove_quotes3(char **arg);
int		*fill_arr(char **tmp3, t_list *node);
int		expander(t_list *head, char **env);
int		duper(int flag);
int		start_or_end(int flag);
void	end_of_program(void);
int		ft_count_word(char *s, char sep);
void	get_terminal_attr(struct termios *original_termios);

#endif
