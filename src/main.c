/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/18 16:08:00 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exit_status = 0;

// func for tests
void	print_og_env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

// OLHA main
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	char	**env_array;
// 	t_input	*words;
// 	t_env	*env;
// 	char **array; // [[], [], [NULL]] array of input
// 	t_cmnd **cmnd_list; //

// 	env = env_init(envp); // copy of envp
// 	read_history(".minishell_history");
// 	while (42)
// 	{
// 		array = NULL;
// 		words = NULL;
// 		env_array = do_env_array(env, count_list_env(env)); // [[], [], [NULL]]
// 		input = readline("Minishell % ");
// 		if (input == NULL)
// 			break ;
// 		if (*input)
// 			add_history(input);
// 		if (*input == '\0' || !validate_input(input))
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		words = tokenize(words, input); // linked list(type, words, next->) list of input
// 		array = do_input_array(words, count_cmnd_len(words));
// 		cmnd_list = creat_cmnd_list(words, count_cmnds(words));// linked list for every cmnd1 | cmnd2 | cmnd3 -> NULL
// 		// for every cmnd:
// 		while (*cmnd_list)
// 		{
// 			// all work is here: 
// 			what_command(cmnd_list, &env, env_array); //pase cmnd_list
// 			//.
// 			*cmnd_list = (*cmnd_list)->next;
// 		}
// 	}
// 	write_history(".minishell_history");
// 	return (0);
// }

// test func: del later.
void	printf_cmnd_list(t_cmnd **list)
{
	int i, j, n;
	t_cmnd *tmp;

	n = 0;
	i = 0;
	tmp = *list;
	while(tmp)
	{
		printf("\nCOMMAND #%d:\n", ++n);
		printf("arguments list: ");
		while(tmp->argv[i])
		{
			j = 0;
			printf("[");
			while(tmp->argv[i][j])
			{
				printf("%c", tmp->argv[i][j]);
				j++;
			}
			printf("]->");
			i++;
		}
		i = 0;
		printf("NULL\n");
		printf("arguments type list: ");
		while(tmp->argv[i])
		{
			j = 0;
			printf("[");
			while(tmp->argv_type[i][j])
			{
				printf("%d", (int)tmp->argv_type[i][j]);
				j++;
			}
			printf("]->");
			i++;
		}
		i = 0;
		printf("NULL\n");
		if (tmp->rd_in_filename)
			printf("'<</<' filename is: %s\n", tmp->rd_in_filename);
		if (tmp->rd_out_filename)
			printf("'>>/>' filename is: %s\n", tmp->rd_out_filename);
		printf("has rdr_in: %d\n", (int)tmp->rdr_in);
		printf("has rdr_out: %d\n", (int)tmp->rdr_out);
		printf("has appnd: %d\n", (int)tmp->appnd);
		printf("has heredoc: %d\n", (int)tmp->heredoc);
		tmp = tmp->next;
	}
}

// // demo main
int	main(int argc, char **argv, char **envp)
{
	t_input	*words;
	t_env	*env;
	char	*input;
	char	**array;
	char	**env_array;

	env = env_init(envp);
	env_array = do_env_array(env, count_list_env(env));
	while (42)
	{
		array = NULL;
		words = NULL;
		input = readline("Minishell % ");
		if (input == NULL)
			break ;
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		words = tokenize(words, input);
		// creat_cmnd_list(words, count_cmnds(words));
		printf_cmnd_list(creat_cmnd_list(words, count_cmnds(words)));

	}
	return (0);
}
