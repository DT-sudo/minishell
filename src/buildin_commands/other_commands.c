/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/19 20:45:42 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_path_from_env(t_env **env)
{
	while (*env)
	{
		if (ft_strncmp((*env)->key, "PATH", ft_strlen("PATH")) == 0)
			return ((*env)->value);
		env = &((*env)->next);
	}
	return (NULL);
}

char	**input_with_null_terminator(char **input)
{
	int		i;
	char	**new_input;

	i = 0;
	while (input[i])
		i++;
	new_input = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (input[i])
	{
		new_input[i] = ft_strdup(input[i]);
		i++;
	}
	new_input[i] = NULL;
	new_input[i + 1] = NULL;
	return (new_input);
}

char	*find_command_path(char **input, t_env **env)
{
	char	**splited_path;
	char	*path_value;
	char	*path_with_command;
	char	*input_command;
	int		i;

	path_value = get_path_from_env(env);
	if (!path_value)
		return (NULL);
	i = 0;
	splited_path = ft_split(path_value, ':');
	if (!splited_path || !*splited_path)
	{
		if (splited_path)
			free_split(splited_path);
		return (NULL);
	}
	input_command = ft_strjoin("/", input[0]);
	while (splited_path[i])
	{
		path_with_command = ft_strjoin(splited_path[i], input_command);
		if (access(path_with_command, X_OK) == 0)
		{
			/* звільнити тимчасові буфери перед поверненням */
			free(input_command);
			free_split(splited_path);
			return (path_with_command);
		}
		/* звільнити непотрібний шлях перед наступною ітерацією */
		free(path_with_command);
		i++;
	}
	free(input_command);
	free_split(splited_path);
	return (NULL);
}

// Howwwww????????
// void close_fd(void)
// {
//     int fd = 3;
//     while (fd < MAX_FD) {
//         close(fd);
//         fd++;
//     }
// }

int	execute_command(char *path_with_command, char **input)
{
	char	**new_input;
	pid_t	pid;

	new_input = input_with_null_terminator(input);
	pid = fork();
	if (pid == 0)
	{
		execve(path_with_command, new_input, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		free_split(new_input);
	}
	else
	{
		perror("fork");
		free_split(new_input);
		return (-1);
	}
	return (0);
}

int	other_commands_implementation(char **input, t_env **env)
{
	char	*path_with_command;
	int		i;

	path_with_command = find_command_path(input, env);
	if (path_with_command)
	{
		i = execute_command(path_with_command, input);
		free(path_with_command);
		return (i);
	}
	else
	{
		fprintf(stderr, "bash: %s: command not found\n", input[0]);
		return (127);
	}
}
