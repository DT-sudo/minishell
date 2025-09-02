/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:50:40 by dt                #+#    #+#             */
/*   Updated: 2025/08/31 21:00:20 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_modified(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (!new)
		return (NULL);
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = '=';
	while (i < len1 + len2 + 1)
	{
		new[i] = s2[i - len1 - 1];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	count_list_input(t_input *input)
{
	int	i;
	t_input *tmp;

	i = 0;
	if (input == NULL)
		return (0);
	tmp = input;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	count_list_env(t_env *env)
{
	int	i;
	t_env *tmp;

	i = 0;
	if (env == NULL)
		return (0);
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// add deviding by |
char	**do_input_array(t_input *input, int size)
{
	int		i;
	char	**res;
	t_input	*tmp;

	if (input == NULL)
		return (NULL);
	i = 0;
	tmp = input;
	res = malloc(sizeof(char *) * size + 1);
	while (tmp != NULL && i < size)
	{	
		res[i++] = tmp->word;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

char	**do_env_array(t_env *env, int size)
{
	t_env *tmp;
	char **res;
	int i;

	i = 0;
	tmp = env;
	res = malloc(sizeof(char *) * size + 1);
	while(tmp != NULL)
	{
		res[i++] = strjoin_modified(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return res;
}
