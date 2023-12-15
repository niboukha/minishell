/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:41:21 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/07 20:10:23 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>

# define EXIT_SUCCES 0
# define EXIT_FAILURE 1
# define MAXIMUM_HEREDOC 2
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define SYNTAX_ERROR 258
# define VAL_SIGINT 130
# define VAL_SIGQUIT 131

typedef enum t_error
{
	NUM_ARGS,
	PIPE_ERR,
	ACCESS_CMD,
	CMD_NOT_FND,
	HOME_NOT_SET,
	OLDPWD_NOT_SET,
	CHDIR_ERR,
	EXPORT_ERR,
	EXIT_A_ERR,
	EXIT_N_A_R,
	UNSET_ERR,
	ENV_ERR,
	PERM_DEN,
	DIR_ERR,
	FORK_ERR,
}	t_error;

void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		add_sortedexport(t_list **lst, t_list *new);
void		lst_addexport(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));

int			is_builtins(t_minishell *minishell);
int			exec_builtins(t_minishell *minishell);
void		echo(t_minishell *minishell);
void		cd(t_minishell *minishell);
void		export(t_minishell *minishell);
void		b_env(t_minishell *minishell);
void		f_exit(t_minishell *minishell);
void		unset(t_minishell *minishell);
void		pwd(t_minishell *minishell);
int			ft_alphanum(char *str);

void		set_val_key(char *key, char *value);
void		execution(t_minishell *minishell);
t_list		*get_new_envv(char *env);
t_list		*save_env(char **env);
t_list		*add_env(char *str);
char		*find_key_env(char *key);
void		print_export(t_minishell *minishell);
void		exec_in_child(t_minishell *minishell);
bool		exec_child(t_minishell *minishell);

char		**convert_to_env(void);
void		execve_function(t_minishell *minishell);
char		*valid_cmd(t_minishell *minishell);
int			check_slash(char *path);
char		**check_path(void);
t_list		*get_if_exist(t_list **lst, t_list *new);

char		*up_cwd(char *cwd);
void		message_error(t_error err, char *cmd);
void		exit_code(t_error err, char	*cmd);

int			ft_alphanum(char *str);
void		sig_in_process(int signum);
void		sig_in_child(int signum);
void		hide_ctrl(void);

void		free_path(t_minishell *minishell);
void		wait_child(t_minishell *minishell);
void		sig_in_heredoc(int signum);

#endif
