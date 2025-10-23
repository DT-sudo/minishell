/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/20 18:11:08 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_command_path(char **input, t_env **env)
{
	char	**splited_path;
	char	*path_with_command;
	char	*input_command;

	splited_path = init_path_components(input, env);
	if (!splited_path)
		return (NULL);
	input_command = ft_strjoin("/", input[0]);
	path_with_command = try_command_in_dirs(splited_path, input_command);
	if (path_with_command)
	{
		free(input_command);
		free_split(splited_path);
		return (path_with_command);
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

int	handle_direct_path_command(char **input)
{
	int	i;

	if (access(input[0], X_OK) == 0)
	{
		i = execute_command(input[0], input);
		return (i);
	}
	else
	{
		perror(input[0]);
		return (127);
	}
}

int	handle_path_command(char **input, t_env **env)
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

int	other_commands_implementation(char **input, t_env **env)
{
	if (!input || !input[0])
		return (0);
	if (ft_strchr(input[0], '/'))
		return (handle_direct_path_command(input));
	else
		return (handle_path_command(input, env));
}
