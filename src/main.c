/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/09 18:47:21 by dt               ###   ########.fr       */
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
void	printf_cmnd_ls(t_cmnd *list)
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
		printf("NULL\n");
		i = 0;
		while (tmp->rdrs)
		{
			printf("\n#%d redir\nType:%d,\nfilename: %s\n", i++,
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

void	printf_t_input(t_input *list)
{
	t_input *tmp;
	
	tmp = list;
	if (!list)
		exit(1);
	printf("Input tokenized:\n");
	while(list != NULL)
	{
		printf("[%s]-", list->word);
		list = list->next;
	}
	printf("NULL\n\n");
	list = tmp;
	printf("Input types:\n");
	while(list != NULL)
	{
		printf("[%d]-", (int)list->type);
		list = list->next;
	}
	printf("NULL\n");
}

// // demo main
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_input	*words;
	char	*tmp;
	char	*input;
	char	**env_array;

	env = env_init(envp);
	env_array = do_env_array(env, count_env_ls(env));
	while (42)
	{
		words = NULL;
		input = readline("\nMinishell % ");
		if (input == NULL)
			break ;
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		tmp = input; //for free(tmp);
		words = tokenize(words, input);
		printf_t_input(words);
		// words = tokenize(words, dollar_extend(input, &env));
		// creat_cmnd_ls(words);
		// printf_cmnd_ls(creat_cmnd_ls(words));
		// what_command(creat_cmnd_ls(words), &env, env_array);
		// free(tmp);
		// while()
		// {
			
		// }
	}
	return (0);
}
