FUNC = minishell.c \
				helper/lists.c \
				helper/lists_helper.c \
				helper/error.c \
				helper/ft_strs.c \
				helper/ft_split.c \
				helper/ft_strjoin.c \
				helper/ft_strdup.c \
				helper/ft_itoa.c \
				helper/ft_atoi.c \
				helper/ft_strchr.c \
				helper/ft_isalpha.c \
				helper/ft_isdigit.c \
				parssing/here_doc.c \
				parssing/here_doc_helper.c \
				parssing/utils_minishell.c \
				parssing/quots_end.c \
				parssing/add_separator.c \
				parssing/main_parsing.c \
				parssing/main_parssing_helper.c \
				parssing/get_path.c \
				parssing/get_path_helper.c \
				parssing/spliter.c \
				parssing/spliter_helper.c \
				parssing/set_redirections.c \
				parssing/remove_quotes.c \
				parssing/remove_qoutes_helper.c \
				parssing/check_dollar.c \
				parssing/set_env.c \
				parssing/check_rederactions.c \
				parssing/check_red_helper.c \
				parssing/initilizer.c \
				parssing/remove_char_from_arr.c \
				parssing/last_exec.c \
				parssing/expander.c \
				parssing/start_end_manager.c \
				builtins/builtin_funcs.c \
				builtins/ft_echo.c \
				builtins/ft_cd.c \
				builtins/ft_pwd.c \
				builtins/ft_env.c \
				builtins/ft_export.c \
				builtins/ft_export_helper.c \
				builtins/ft_export_h2.c \
				builtins/ft_unset.c \
				builtins/ft_exit.c \
				signal/sigint_handler.c \
				exec/ft_exec_cmd.c \
				exec/fd_handle.c \
				exec/exec_helper.c \


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
RM = rm -f

OBJS = $(FUNC:.c=.o)

%.o: %.c	./includes/minishell.h
		$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
		$(RM) $(OBJS)

fclean: clean
		 $(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
