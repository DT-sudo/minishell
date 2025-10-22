/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/07 23:36:55 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_command_implementation(t_cmnd **cmnd_ls, t_env **env)
{
	int	i;
	int	y;
	int	n_FLAG;

	n_FLAG = 0;
	i = 1;
	y = 1;
	if ((*cmnd_ls)->argv[i] && ft_strncmp((*cmnd_ls)->argv[1], "-n", 3) == 0)
	{
		n_FLAG = 1;
		y = 2;
	}
	while ((*cmnd_ls)->argv[y] != NULL)
	{
		printf("%s", (*cmnd_ls)->argv[y]);
		if ((*cmnd_ls)->argv[y + 1])
			printf(" ");
		y++;
	}
	if (n_FLAG == 0)
		printf("\n");
	return (0);
}
