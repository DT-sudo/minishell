/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/15 20:54:48 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exit_status = 0;

void	printf_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("key: %s, value: %s\n", env->key, env->value);
		env = env->next;
	}
}

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
		printf("----------------------------------------------");
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
	t_input	*tmp;

	tmp = list;
	if (!list)
		exit(1);
	printf("\nInput tokenized:\n");
	while (list != NULL)
	{
		printf("[%s]-", list->word);
		list = list->next;
	}
	printf("NULL\n");
	list = tmp;
	// printf("Input types:\n");
	// while(list != NULL)
	// {
	// 	printf("[%d]-", (int)list->type);
	// 	list = list->next;
	// }
	// printf("NULL\n");
}

void	print_extened_input(char *s)
{
	if (!s)
		exit(1);
	printf("\nExtended input:\n");
	while (*s)
	{
		printf("%c", *s);
		s++;
	}
	printf("\n\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_input	*words;
	char	*tmp;
	char	*input;
	char	**env_array;
	t_cmnd	*list; 

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
		input = dollar_extend(input, &env);
		
		print_extened_input(input);// "debug"
		
		words = tokenize(words, input); // creates linked list of tokenized input
		list = creat_cmnd_ls(words);    // creats linked list of commands
		
		// printf_cmnd_ls(list); // "debug" prints all stuff
		
		what_command(&list, &env, env_array);
		
	}
	return (0);
}

// tmp = input; //for free(tmp);  del
// words = tokenize(words, input);
// printf_t_input(words);// del

// printf("\n///////////Extendet dolla part///////////\n\n");// del

// words = NULL;// del
// input = tmp;// del