/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:16 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_status = 0;

void	free_input(t_input *words)
{
	t_input	*tmp;

	while (words)
	{
		tmp = words;
		words = words->next;
		free(tmp->word);
		free(tmp);
	}
}

void	free_list(t_cmnd *list)
{
	t_cmnd	*tmp;
	t_rdrs	*rdr_tmp;
	int		i;

	while (list)
	{
		tmp = list;
		list = list->next;
		i = 0;
		while (tmp->argv && tmp->argv[i])
			free(tmp->argv[i++]);
		free(tmp->argv);
		i = 0;
		while (tmp->full_argv && tmp->full_argv[i])
			free(tmp->full_argv[i++]);
		free(tmp->full_argv);
		i = 0;
		while (tmp->argv_type && tmp->argv_type[i])
			free(tmp->argv_type[i++]);
		free(tmp->argv_type);
		while (tmp->rdrs)
		{
			rdr_tmp = tmp->rdrs;
			tmp->rdrs = tmp->rdrs->next;
			free(rdr_tmp->filename);
			free(rdr_tmp);
		}
		free(tmp);
	}
}

void	print_env(t_env *env)
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
void	print_cmnd_ls(t_cmnd *list)
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

void	print_input(t_input *list)
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
	read_history(".minishell_history");
	env_array = do_env_array(env, count_env_ls(env));
	// init_signals();
	while (42)
	{
		words = NULL;
		input = readline("Minishell % ");
		// signal(SIGINT, handler_sig_int);
		if (input == NULL)
		{
			g_exit_status = exit_command_implementation(&env, env_array);
			break ;
		}
		if (*input)
			add_history(input);
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		input = dollar_extend(input, &env, g_exit_status);
		// print_extened_input(input);// "debug"
		words = tokenize(words, input);
		// creates linked list of tokenized input
		list = crt_cmnd_ls(words); // creats linked list of commands
		// print_cmnd_ls(list); // "debug" prints all stuff
		what_command(&list, &env, env_array);
	}
	write_history(".minishell_history");
	return (0);
}
