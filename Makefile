# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niboukha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/29 10:55:39 by niboukha          #+#    #+#              #
#    Updated: 2023/08/08 14:30:57 by niboukha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -I/goinfre/niboukha/homebrew/opt/readline/include

SRC_PARSING = parsing/collect_string.c\
				parsing/ft_command_utils.c\
				parsing/ft_split_.c\
				parsing/parser.c\
				parsing/tools.c\
				parsing/expand.c\
				parsing/ft_node_utils.c\
				parsing/open_files.c\
				parsing/redirections.c\
				parsing/tools1.c\
				parsing/extract_string.c\
				parsing/ft_redir_utils.c\
				parsing/open_here_doc.c\
				parsing/syntax_error.c\
				parsing/parser_utils.c

SRC_EXECUTION = execution/builtins.c\
				execution/env.c\
				execution/exit.c\
				execution/export_util.c\
				execution/pwd.c\
				execution/cd.c\
				execution/execute_cmd.c\
				execution/exit_function.c\
				execution/get_env.c\
				execution/unset.c\
				execution/echo.c\
				execution/execution.c\
				execution/export.c\
				execution/valide_path.c\
				execution/env_utils.c\
				execution/execution_utils.c\
				execution/multi_pipes.c

SRC_MAIN = minishell.c\
			signals.c\
			init_g_struct.c

LIB = -lreadline -L/goinfre/niboukha/homebrew/opt/readline/lib

OBJ = $(SRC_PARSING:.c=.o) $(SRC_EXECUTION:.c=.o) $(SRC_MAIN:.c=.o)

all : $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LIB) $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT) :
	cd libft && make && make bonus

clean :
	@rm -f $(OBJ)
	cd libft && make clean

fclean : clean
	@make fclean -C libft/
	@rm -f $(NAME)

re : fclean all

.PHONY: all re clean fclean
