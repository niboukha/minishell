# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niboukha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 19:21:41 by niboukha          #+#    #+#              #
#    Updated: 2023/07/25 16:20:46 by niboukha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_isalpha.c ft_isprint.c ft_memcpy.c ft_strchr.c ft_strlcat.c \
ft_strlcpy.c ft_strmapi.c ft_strlen.c ft_strrchr.c ft_strdup.c ft_bzero.c ft_isascii.c \
ft_memchr.c ft_memmove.c ft_strncmp.c ft_tolower.c ft_isalnum.c ft_isdigit.c ft_memcmp.c \
ft_memset.c ft_toupper.c  ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_itoa.c ft_strnstr.c\
ft_strcmp.c check_sep.c\

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)

bonus : $(OBJ_BONUS)
	@ar -rc $(NAME) $(OBJ_BONUS)

.c.o:
	@$(CC) -c $< -o ${<:.c=.o}

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
