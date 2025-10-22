/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/19 20:47:04 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command_implementation(t_env **my_env, char **array_env)
{
	t_env	*curr;
	t_env	*next;
	int		i;

	if (my_env && *my_env)
	{
		curr = *my_env;
		while (curr)
		{
			next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			curr = next;
		}
		*my_env = NULL;
	}
	if (array_env)
	{
		i = 0;
		while (array_env[i])
		{
			if (array_env[i])
				free(array_env[i]);
			i++;
		}
		free(array_env);
		array_env = NULL;
	}
	ft_printf("Exiting minishell...\n");
	g_exit_status = 0;
	exit(g_exit_status);
}
