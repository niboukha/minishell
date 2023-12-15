/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:34 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 15:09:48 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "execution.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_global
{
	t_list	*tenv;
	int		exit_code;
	char	*tmp_pwd;
	int		flag;
	int		hdoc;
	int		std_in;
	int		std_out;
	int		is_child;
	int		flg;
}			t_global;

void	init_struct(int ac, char **env);
int		check_input(char *str, char **s);

t_global	*g_data;

#endif
