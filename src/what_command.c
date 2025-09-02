/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/01 19:08:37 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

//WRONG LOGIC !!!

bool	is_command_buildin(char **input)
{
    t_input *f_token;

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

void	which_buildin_command(char **input, t_env *my_env, char **array_env)
{
	int	exit_status;


	if (ft_strncmp(input[0], "echo", 4) == 0)
		exit_status = echo_command_implementation(input);
	else if (ft_strncmp(input[0], "pwd", 3) == 0)
		pwd_command_implementation(my_env);
	else if (ft_strncmp(input[0], "export", 6) == 0)
		export_command_implementation(input, my_env, array_env);
	// else if (ft_strncmp(input[0], "unset", 5) == 0)
	// 	unset_command_implementation(my_env);
	else if (ft_strncmp(input[0], "cd", 2) == 0)
		cd_command_implementation(input, my_env);
	// else if (ft_strncmp(input[0], "exit", 4) == 0)
		// exit_command_implementation(my_env);
	else if (ft_strncmp(input[0], "env", 3) == 0)
		print_my_env(my_env);
	ft_printf("which_buildin_command: %s\n", input[0]);
	ft_printf("exit_status: %d\n", exit_status);
}

void	what_command(char** input, t_env *my_env, char** array_env)
{
	if (is_command_buildin(input))
		which_buildin_command(input, my_env, array_env);
        
	
		// else
		// {
		// 	char *cmd[] = {input->word, NULL};
		// // Execute the command with the environment
		// 	execve(input->word, cmd, my_env);
		// // Print error if execve fails
		// 	perror("execve");
		// }
}
