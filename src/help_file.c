// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   help_file.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/08/18 15:50:05 by olcherno          #+#    #+#             */
// /*   Updated: 2025/08/26 16:08:02 by dt               ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// t_input	*initialize_command(void)
// {
// 	t_input *cmd;

// 	cmd = malloc(sizeof(t_input));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->type = TOKEN_WORD; // ??
// 	cmd->next = NULL;
// 	cmd->word = "echo";
// 	// cmd->argv = malloc(sizeof(char *) * 6);
// 	if (!cmd->argv)
// 	{
// 		free(cmd);
// 		return (NULL);
// 	}
// 	cmd->argv[0] = ft_strdup("echo");
// 	cmd->argv[1] = ft_strdup("-n");
// 	cmd->argv[2] = ft_strdup("ASD");
// 	cmd->argv[3] = ft_strdup("ASD");
// 	cmd->argv[4] = ft_strdup("ASD");
// 	cmd->argv[5] = NULL;
// 	return (cmd);
// }