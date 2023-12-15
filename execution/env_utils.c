/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:46:45 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/03 22:09:23 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_alphanum(char *str)
{
	int	i;

	i = -1;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

char	**convert_to_env(void)
{
	t_list	*tmp;
	char	**env;
	int		len;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (ft_lstsize(g_data->tenv) + 1));
	tmp = g_data->tenv;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2;
		env[i] = calloc (sizeof(char), len);
		env[i] = ft_strjoin(env[i], tmp->key);
		env[i] = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(env[i], tmp->value);
		++i;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	*find_key_env(char *key)
{
	t_list	*tmp;

	tmp = g_data->tenv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
