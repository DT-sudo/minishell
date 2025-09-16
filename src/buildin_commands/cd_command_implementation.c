/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:44 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/11 16:42:10 by dtereshc         ###   ########.fr       */
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
	// Find and update PWD
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
    t_env *tmp;

    // Print PWD
    tmp = env;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->key, "PWD") == 0)
        {
            printf("pwd=%s\n", tmp->value);
            break;
        }
        tmp = tmp->next;
    }

    // Print OLDPWD
    tmp = env;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->key, "OLDPWD") == 0)
        {
            printf("oldpwd=%s\n", tmp->value);
            break;
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
	printf("cd: ++++++++++++++++++++++++++ %s\n", path);
	return (0);
}
int	previous_dir(char **input, t_env *env)
{
    char *path = NULL;
    t_env *tmp = env;
    char cwd[PATH_MAX];
    char prev_dir[PATH_MAX];

    // Find OLDPWD in env
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "OLDPWD") == 0)
        {
            path = tmp->value;
            break;
        }
        tmp = tmp->next;
    }
    if (!path || !*path)
        return (printf("cd: OLDPWD not set\n"), 1);

    // Save current dir before chdir
    if (!getcwd(prev_dir, sizeof(prev_dir)))
        return (perror("getcwd"), 1);

    if (chdir(path) == -1)
        return (perror("cd"), 1);

    // Print new directory
    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        perror("getcwd");

    // Update OLDPWD to prev_dir
    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "OLDPWD") == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(prev_dir);
            break;
        }
        tmp = tmp->next;
    }
    // Update PWD to cwd
    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "PWD") == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(cwd);
            break;
        }
        tmp = tmp->next;
    }
    return 0;
}

int	standard_cd(char **input, t_env *env)
{
	char	*path;
	char	cwd[PATH_MAX];

	path = input[1];
	change_oldpwd(env);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	change_pwd(env);
	return (0);
}

int	cd_command_implementation(char **input, t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_cd(input, env));
	}
	else if ((input[i] != NULL) && (input[i + 1] == NULL))
	{
		if (ft_strcmp(input[i], "-") == 0)
			return (previous_dir(input, env));
		else if (ft_strcmp(input[i], "~") == 0)
			return (only_cd(input, env));
		else
			return (standard_cd(input, env));
	}
	else
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	return (0);
}

// 	tmp = env;
// while (tmp != NULL)
// {
// 	// printf("oldpwdlooking");
// 	if (ft_strcmp(tmp->key, "PWD") == 0)
// 	{
// 		break ;
// 	}
// 	tmp = tmp->next;
// }
// printf("pwd=%s", tmp->value);
// 	tmp = env;
// while (tmp != NULL)
// {

// 	if (ft_strcmp(tmp->key, "OLDPWD") == 0)
// 	{
// 		break ;
// 	}
// 	tmp = tmp->next;
// }
// printf("oldpwd=%s", tmp->value);
// return (0);