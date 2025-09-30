/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/30 18:11:39 by dt               ###   ########.fr       */
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

// test func: del later.
void	printf_cmnd_list(t_cmnd *list)
{
	t_cmnd	*tmp;

	int i, j, n;
	n = 0;
	i = 0;
	tmp = list;
	while (tmp)
	{
		printf("\nCOMMAND #%d:\n", ++n);
		printf("Full arguments: ");
		while (*(tmp->full_argv))
		{
			printf("[%s]->", *(tmp->full_argv));
			tmp->full_argv++;
		}
		printf("NULL\n");
		printf("Arguments type list: ");
		while (*(tmp->argv_type))
		{
			printf("[%d]->", (int)**(tmp->argv_type));
			tmp->argv_type++;	
		}
		printf("NULL\n");
		printf("Arguments list: ");
		while (*(tmp->argv))
		{
			printf("[%s]->", *(tmp->argv));
			tmp->argv++;
		}
		printf("NULL");
		i = 0;
		while (tmp->rdrs)
		{
			printf("\n\n#%d redir\nType:%d,\nfilename: %s\n", i++,
				(int)tmp->rdrs->redir_type, tmp->rdrs->filename);
			tmp->rdrs = tmp->rdrs->next;
		}
		printf("\nhas rdr_in: %d\n", (int)tmp->rdr_in);
		printf("has rdr_out: %d\n", (int)tmp->rdr_out);
		printf("has appnd: %d\n", (int)tmp->appnd);
		printf("has heredoc: %d\n", (int)tmp->heredoc);
		printf("has pipe: %d\n", (int)tmp->pipe);
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
		input = readline("\nMinishell % ");
		if (input == NULL)
			break ;
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		words = tokenize(words, input);
		// creat_cmnd_list(words);
		printf_cmnd_list(creat_cmnd_list(words));
		// what_command(creat_cmnd_list(words), &env, env_array);
	}
	return (0);
}
