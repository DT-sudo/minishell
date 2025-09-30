// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pwd_command_implementation.c                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/08/16 23:50:56 by olcherno          #+#    #+#             */
// /*   Updated: 2025/08/31 23:04:08 by olcherno         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// int pwd_command_implementation(t_env *env)
// {
//     char cwd[PATH_MAX];

//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//         printf("%s\n", cwd);
//     else
//         perror("pwd");
//     return 0;
// }
