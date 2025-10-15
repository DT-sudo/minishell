/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/10/15 20:57:39 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	which_buildin_command(t_cmnd *cmnd, t_env **my_env, char **array_env)
{
	if (ft_strncmp(cmnd->full_argv[0], "echo", 4) == 0) // argv --> full_argv
		return (echo_command_implementation(&cmnd, my_env));
	// else if (ft_strncmp(cmnd->argv[0], "pwd", 3) == 0)
	// 	return (pwd_command_implementation(*my_env));
	// else if (ft_strncmp(cmnd->argv[0], "export", 6) == 0)
	// 	return (export_command_implementation(cmnd->argv, my_env, array_env));
	// else if (ft_strncmp(cmnd->argv[0], "unset", 5) == 0)
	// 	return (unset_command_implementation(my_env, cmnd->argv));
	// else if (ft_strncmp(cmnd->argv[0], "cd", 2) == 0)
	// 	return (cd_command_implementation(cmnd->argv, *my_env));
	// else if (ft_strncmp(cmnd->argv[0], "exit", 4) == 0)
	// 	return (exit_command_implementation(my_env));
	// else if (ft_strncmp(cmnd->argv[0], "env", 3) == 0)
	// {
	// 	print_my_env(*my_env);
	// 	return (0); // ?...
	// }
	return (0); // ?...
}

void	what_command(t_cmnd **cmnd_ls, t_env **my_env, char **array_env)
{
	t_cmnd	*cmnd;

	cmnd = *cmnd_ls;
	while (cmnd != NULL)
	{
		if (is_command_buildin(cmnd->argv))
			exit_status = which_buildin_command(cmnd, my_env, array_env);
		else
			exit_status = other_commands_implementation(cmnd->argv, my_env);
		cmnd = cmnd->next;
	}
}
