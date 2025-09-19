/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/19 16:32:19 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Define the global variable

// WRONG LOGIC !!!

bool	is_command_buildin(char **input)
{
	t_input	*f_token;

	if (ft_strncmp(input[0], "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(input[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(input[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(input[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(input[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(input[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(input[0], "exit", 4) == 0)
		return (true);
	else
		return (false);
}
// del input replace on *cmnd_list->argv[i] within func and parse only cmd_list
void	which_buildin_command(t_cmnd **cmnd_list, t_env **my_env,
		char **array_env)
{
	t_cmnd	*input;

	input = *cmnd_list;
	if (ft_strncmp(input->argv[0], "echo", 4) == 0)
		exit_status = echo_command_implementation(&input, my_env);
			// pase cmnd_list
	else if (ft_strncmp(input->argv[0], "pwd", 3) == 0)
		exit_status = pwd_command_implementation(*my_env);
	else if (ft_strncmp(input->argv[0], "export", 6) == 0)
		exit_status = export_command_implementation(input->argv, my_env, array_env); // del input
	else if (ft_strncmp(input->argv[0], "unset", 5) == 0)
		exit_status = unset_command_implementation(my_env, input->argv); // del input
	else if (ft_strncmp(input->argv[0], "cd", 2) == 0)
		exit_status = cd_command_implementation(input->argv, *my_env); // del input
	// else if (ft_strncmp(input->argv[0], "exit", 4) == 0)
	// exit_command_implementation(my_env); //del input
	else if (ft_strncmp(input->argv[0], "env", 3) == 0)
	{
		print_my_env(*my_env);
		exit_status = 0;
	}
	// Temporary debug - remove this later
	// printf("DEBUG: Command '%s' returned exit_status: %d\n", input[0], exit_status);
}

// pase cmnd_list
void	what_command(t_cmnd **cmnd_list, t_env **my_env, char **array_env)
{
	t_cmnd	*input;

	input = *cmnd_list;
	if (is_command_buildin(input->argv))
	{
		which_buildin_command(cmnd_list, my_env, array_env);
	}
	// External commands need a new process: fork + execve	
	// else
	// {
	// 	char *cmd[] = {input->word, NULL};
	// // Execute the command with the environment
	// 	execve(input->word, cmd, my_env);
	// // Print error if execve fails
	// 	perror("execve");
}
