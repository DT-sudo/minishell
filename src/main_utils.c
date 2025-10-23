/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:22:18 by dt                #+#    #+#             */
/*   Updated: 2025/10/23 16:22:30 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
