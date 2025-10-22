/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/07 23:38:50 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_two_var(char **input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input[count])
		count++;
	return (count);
}

int	two_var(char **input, t_env **env)
{
	int	result1;
	int	result2;

	result1 = one_var(input[1], env);
	result2 = one_var(input[2], env);
	if (result1 != 0)
		return (result1);
	return (result2);
}

int	parsing_export(char **input, t_env **env)
{
	char	*var_name;
	char	*var_value;

	if (input[1][0] >= '0' && input[1][0] <= '9' || ft_strchr(input[1], '+')
		|| input[1][0] == '=')
	{
		print_array_error(input);
		return (1);
	}
	else if (is_two_var(input) > 2)
	{
		return (two_var(input, env));
	}
	else
	{
		return (one_var(input[1], env));
	}
	return (0);
}

int	export_command_implementation(char **input, t_env **env, char **array_env)
{
	int	i;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_export(input, *env));
	}
	else if ((input[i] != NULL))
	{
		return (parsing_export(input, env));
	}
	return (0);
}
