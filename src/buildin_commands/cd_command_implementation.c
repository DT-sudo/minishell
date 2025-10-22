/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:42:41 by dt                #+#    #+#             */
/*   Updated: 2025/10/19 20:42:43 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(t_env *env)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	t_env	*tmp;

	if (!getcwd(newpwd, sizeof(newpwd)))
		return ;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(newpwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_oldpwd(t_env *env)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	t_env	*tmp;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return ;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	print_pwd_and_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			printf("pwd=%s\n", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			printf("oldpwd=%s\n", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	only_cd(char **input, t_env *env)
{
	char	*path;
	t_env	*tmp;
	char	cwd[PATH_MAX];

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
		{
			path = tmp->value;
		}
		tmp = tmp->next;
	}
	change_oldpwd(env);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	change_pwd(env);
	return (0);
}

char	*get_env_value(t_env *env, const char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
