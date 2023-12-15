/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:32:36 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 12:16:03 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include "../libft/libft.h"

# define UNEXPECTED_TOKEN "syntax error near unexpected token"
# define IN 1
# define TRUNC 2
# define APPEND 3
# define HERE_DOC 4

typedef struct s_data
{
	char	*content;
	int		*i;
}			t_data;

typedef struct s_files
{
	char			*file;
	int				type;
	int				flag;
	int				fd;
	struct s_files	*next;
}					t_files;

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}					t_node;

typedef struct s_head
{
	t_node	*h_node;
	t_files	*h_files;
}			t_head;
typedef struct s_minishell
{
	char				**cmd;
	char				**path;
	int					infile;
	int					outfile;
	int					len;
	int					fd[2];
	pid_t				pid;
	t_files				*redir;
	struct s_minishell	*next;
}						t_minishell;

char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_join(char *s1, char *s2);
void		skip_whitespace(t_data *data);
t_minishell	*parser(char *input);
t_node		*collect_node(t_data *data);
bool		return_head_2(t_data *data, t_minishell **head,
				t_node **head_list, t_files **head_redi);
t_head		*return_head(t_data *data, char *input, int *i, t_minishell **head);
t_files		*redirections(t_data *data);
char		*extract_string_within_quotes(char *str);
char		*collect_string(t_data *data, int *here_doc, int flag);
char		*ft_expand(t_data *data);
char		**ft_split_(char *str);
char		*ft_itoa(int n);
bool		syntax_error(char *next);
int			check_quotes(char *str);
int			ft_isalpha(int a);
void		exit_with_status(int exit_status);

void		_ft_lst_clear(t_node **lst, void (*del)(void *));
void		toggle_char(char *str);
t_node		*_ft_lst_last(t_node *lst);
t_node		*_ft_lst_new(char *content);
void		_ft_lst_add_back(t_node **lst, t_node *new);
int			_ft_lst_size(t_node *lst);

t_files		*ft_files_new(char *file, int type);
t_files		*ft_last_files(t_files *redir);
void		ft_add_back_redir(t_files **head, t_files *new);
void		ft_clear_redir(t_files **head);

int			ft_isalnum(int c);
int			ft_isdigit(int c);
short		ft_perror(int err, char *reas);

t_minishell	*create_command_node(t_head *_head);
t_minishell	*ft_last_command(t_minishell *head);
void		ft_command_add_back(t_minishell **head, t_minishell *new);
void		ft_clear_list_commands(t_minishell **head);

void		open_files_and_here_docs(t_minishell *head);
bool		open_here_docs(t_minishell *head);
int			ftlstsize(t_minishell *lst);

bool		syntax_error2(char *next);
char		*_abs(char *str);

#endif
