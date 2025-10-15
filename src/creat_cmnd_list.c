/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmnd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:44 by dt                #+#    #+#             */
/*   Updated: 2025/10/15 19:56:56 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns pointer to the next command from t_input words
t_input	*move_ptr_cmnd(t_input *next_cmnd)
{
	if (next_cmnd == NULL)
		return (NULL);
	while (next_cmnd != NULL && next_cmnd->type != TOKEN_PIPE)
		next_cmnd = next_cmnd->next;
	if (next_cmnd != NULL && next_cmnd->type == TOKEN_PIPE)
		return (next_cmnd->next);
	return (NULL);
}

//not sure if its needed
void	set_apnd_hered_pipe(t_cmnd *node)
{
	int	i;

	i = 0;
	while (node->argv_type[i])
	{
		if ((*(node->argv_type[i])) == TOKEN_APPND)
			node->appnd = true;
		else if (*(node->argv_type[i]) == TOKEN_HERE)
			node->heredoc = true;
		else if (*(node->argv_type[i]) == TOKEN_RDR_IN)
			node->rdr_in = true;
		else if (*(node->argv_type[i]) == TOKEN_RDR_OUT)
			node->rdr_out = true;
		i++;
	}
}

void do_rdrs(t_cmnd *node)
{
	t_rdrs *rdr_node;
	t_rdrs *prev_node;
	int i;
	
	i = 0;
	prev_node = NULL;
	while(node->full_argv[i])
	{
		if(*(node->argv_type[i]) >= TOKEN_RDR_IN && *(node->argv_type[i]) <= TOKEN_HERE)
		{
			if (!(node->argv_type[i + 1]))
				break; 
			rdr_node = malloc(sizeof(t_rdrs));
			if (!rdr_node)
				exit(1);
			rdr_node->redir_type = *(node->argv_type[i]);
			rdr_node->filename = node->full_argv[i + 1];
			rdr_node->next = NULL;
			if (node->rdrs == NULL)
				node->rdrs = rdr_node;
			else 
				prev_node->next = rdr_node;
			prev_node = rdr_node;
			i += 2;
			continue;
		}
		i++;
	}
}

// setup of each cmnd node
t_cmnd	*setup_cmnd_node(t_cmnd *node, t_input *next_cmnd)
{
	t_cmnd		*new_node;
	int size_argv;
	int size;
	
	size_argv = count_cmnd_len_argv(next_cmnd);
	size = count_cmnd_len(next_cmnd);
	do_cmnd_array(next_cmnd, node, size_argv);
	do_full_cmnd_array(next_cmnd, node, size);
	do_cmnd_array_type(next_cmnd, node, size);
	do_rdrs(node);
	set_apnd_hered_pipe(node);
	return (node);
}

// main outter func
t_cmnd	*creat_cmnd_ls(t_input *words)
{
	int		cmnd_qntt;
	t_cmnd	*cmnd_node;
	t_cmnd	*prev_node;
	t_cmnd	*list;

	if (words == NULL)
		return (NULL);
	cmnd_qntt = count_cmnds(words);
	list = NULL;
	while(cmnd_qntt--)
	{
		cmnd_node = malloc(sizeof(t_cmnd));
		if (cmnd_node == NULL)
		{
			// add free()
			exit(1);
		}
		set_to_zero(cmnd_node);
		cmnd_node = setup_cmnd_node(cmnd_node, words);
		if (!list)
		{
			list = cmnd_node;
			prev_node = list;
		}
		else
		{
			prev_node->next = cmnd_node;
			prev_node = cmnd_node;
		}
		words = move_ptr_cmnd(words);
	}
	return (list);
}


