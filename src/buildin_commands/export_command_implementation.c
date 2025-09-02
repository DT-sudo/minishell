/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/01 20:11:11 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_array_size(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

char	**bubble_sort(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

int	only_export(char **input, char **array_env)
{
	char	**sorted_env;
	int		i;

	sorted_env = bubble_sort(array_env, get_array_size(array_env));
	if (!sorted_env)
		return (1);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);
	return (0);
}

// int parsing_export(char **input, t_env *env)
// {
//     char	*var_name;
//     char	*var_value;
// 	if (input[1][0] >= "0" && input[1][0] <= "9")
// 	{
// 		print_error_message("Invalid variable name");
// 	}
// 	return (0);
// }


int	export_command_implementation(char **input, t_env *env, char **array_env)
{
	int i;
	t_env *tmp;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_export(input, array_env));
	}
	// else if ((input[i] != NULL) && (input[i + 1] == NULL))
	// {
    //     return (parsing_export(input, env));
	// }

	return (0);
}
