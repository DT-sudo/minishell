/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:43:27 by dt                #+#    #+#             */
/*   Updated: 2025/10/07 23:38:37 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_modified(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlenn(s1);
	len2 = ft_strlenn(s2);
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

char	**do_env_array(t_env *env, int size)
{
	t_env	*tmp;
	char	**res;
	int		i;

	i = 0;
	tmp = env;
	res = malloc(sizeof(char *) * size + 1);
	while (tmp != NULL)
	{
		res[i++] = strjoin_modified(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (res);
}

int	count_env_ls(t_env *env)
{
	int		i;
	t_env	*tmp;

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
