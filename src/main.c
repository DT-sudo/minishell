/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/06 18:40:53 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// // test main
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	char	**array;
// 	t_input	*words;
// 	t_env	*env;

// 	t_env	*env_tmp;
// 	t_input *tmp_wrds;
// 	char 	**env_array;
// 	int		i;

// 	env = env_init(envp);
// 	////
// 	// env_tmp = env;
// 	// env_array = do_env_array(env, count_list_env(env));
// 	// i = 0;
// 	// printf("ENV LIST:\n");
// 	// while(env_tmp != NULL)
// 	// {
// 	// 	printf("#%d %s=%s\n", i++, env_tmp->key, env_tmp->value);
// 	// 	env_tmp = env_tmp->next;
// 	// }
// 	// i = 0;
// 	// printf("\nENV ARRAY:\n");
// 	// while(i < (count_list_env(env) + 1))
// 	// {
// 	// 	printf("#%d %s\n", i, env_array[i]);
// 	// 	i++;
// 	// }
// 	////
// 	while (42)
// 	{
// 		i = 0;
// 		tmp_wrds = NULL;
// 		array = NULL;
// 		words = NULL;
// 		input = readline("Minishell % ");
// 		if (input == NULL)
// 			break ;
// 		if (*input == '\0' || !validate_input(input))
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		words = tokenize(words, input);
// 		tmp_wrds = words;
// 		while (tmp_wrds != NULL)
// 		{
// 			i += 1;
// 			printf("\n#%d. word: %s, type: %d", i, tmp_wrds->word,
				// tmp_wrds->type);
// 			tmp_wrds = tmp_wrds->next;
// 		}
// 		printf("\n");
// 		array = do_input_array(words, count_list_input(words));
// 		env_array = do_env_array(env, count_list_env(env));
// 		///
// 		i = 0;
// 		// array = do_input_array(words, count_list_input(words));
// 		printf("\n\nLenght of the list: %d\n\n", count_list_input(words));
// 		while (array[i])
// 			printf("%s -> ", array[i++]);
// 		printf("%s\n", array[i]);
// 		///
// 		free(input);
// 		free(words);
// 	}
// 	return (0);
// }

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
		creat_cmnd_list(words, count_cmnds(words));
		// array = do_array(words, count_list_input(words)); //del this

		////								pseodo_code
		// t_cmnd **cmnd_list;
		//		// 1. MALLOC T_CMND LIST 
		// cmnd_list = malloc(sizeof(t_cmnd *) * count_cmnds(words)); 
		//		// 2. SAVE EVERY COMMAND TO SEPARATED NODE in t_cmnd linked list and setup every t_cmnd parametr
		// cmnd_list = do_cmnd_list(array); // does linked_list of commands from the input devided with |
		// 		// 3. DO WHILE LOOP FOR EXECUTING EVERY COMMAND FROM LIKED LIST
		// while(cmnd_list)
		// {
			// if(is_builtin_func(cmnd_list))
			// {
				//res_to_pass_to_next = do_builtin_cmnd(cmnd_list);
			// }
			// else
			// {
				// res_to_pass_to_next = do_extended_cmnd(cmnd_list); -> do_extended_cmnd(cmnd_list) == execve() + fork()
			// }
			// cmnd_list = cmnd_list->next;
		// }
		// free(input);
		// free(words);
	}
	return (0);
}
