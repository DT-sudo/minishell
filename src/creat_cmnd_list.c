/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmnd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:44 by dt                #+#    #+#             */
/*   Updated: 2025/09/16 13:05:12 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns pointer to the next command from t_input words
t_input	*move_ptr_cmnd(t_input *next_cmnd)
{
	if (next_cmnd == NULL)
		return (NULL);
	while (next_cmnd != NULL && next_cmnd->type != TOKEN_PIPE && next_cmnd != 0)
		next_cmnd = next_cmnd->next;
	if (next_cmnd != NULL && next_cmnd->type == TOKEN_PIPE)
		return (next_cmnd->next);
	return (NULL);
}

// sets node appnd/heredoc/pipe with argv_type
void	set_apnd_hered_pipe(t_cmnd *node)
{
	int	i;

	i = 0;
	while (node->argv_type[i])
	{
		if ((*(node->argv_type[i])) == TOKEN_APPND)
		{
			node->appnd = true;
			// write(1, "tr1\n", 4);
		}
		else if (*(node->argv_type[i]) == TOKEN_HERE)
		{
			node->heredoc = true;
			// write(1, "tr2\n", 4);
		}
		i++;
	}
}

// sets filename after >>\>\<\<<
void	set_filename(t_cmnd *node)
{
	int	i;

	i = 0;
	while ((node->argv_type[i]) != NULL
		&& !(*(node->argv_type[i]) >= TOKEN_RDR_IN
			&& *(node->argv_type[i]) <= TOKEN_HERE))
		i++;
	if (node->argv_type[i] != NULL && node->argv[i + 1] != NULL)
	{
		if ((*(node->argv_type[i]) == TOKEN_RDR_IN
				|| *(node->argv_type[i]) == TOKEN_HERE))
			node->rd_in_filename = node->argv[i + 1];
		else if ((*(node->argv_type[i]) == TOKEN_RDR_OUT
				|| *(node->argv_type[i]) == TOKEN_APPND))
			node->rd_out_filename = node->argv[i + 1];
	}
}

// puts values to every t_cmnd node and connect them to each other 
void	list_nodes(t_cmnd *node, t_cmnd **list, int cmnd_qntt)
{
	int			j;
	static int	i = 0;

	j = 0;
	if (node == NULL)
		return ;
	list[i] = node;
	i++;
	if (i == cmnd_qntt)
	{
		while (j < cmnd_qntt - 1)
		{
			list[j]->next = list[j + 1];
			j++;
		}
		list[j]->next = NULL;
		i = 0;
	}
}

// setup of each cmnd node and list them together
t_cmnd	*setup_cmnd_node(t_cmnd *node, t_input *next_cmnd, int cmnd_qntt,
		t_cmnd **list, int dpth)
{
	t_cmnd	*new_node;

	do_cmnd_array(next_cmnd, node, count_cmnd_len(next_cmnd));
	do_cmnd_array_type(next_cmnd, node, count_cmnd_len(next_cmnd));
	set_apnd_hered_pipe(node);
	set_filename(node);
	list_nodes(node, list, cmnd_qntt);
	if (dpth < cmnd_qntt - 1)
	{
		next_cmnd = move_ptr_cmnd(next_cmnd);
		// printf("\n%s\n", next_cmnd->word);
		if (next_cmnd == NULL)
			return (node);
		new_node = malloc(sizeof(t_cmnd));
		if (new_node == NULL)
		{
			// add free()
			exit(0);
		}
		set_to_zero(new_node);
		new_node = setup_cmnd_node(new_node, next_cmnd, cmnd_qntt, list, dpth
				+ 1);
	}
	return (node);
}

// main func
t_cmnd	**creat_cmnd_list(t_input *words, int size)
{
	int		i;
	int		cmnd_qntt;
	t_cmnd	*cmnd_node;
	t_cmnd	**list;

	if (words == NULL)
		return (NULL);
	i = 0;
	// count_cmnds == cmnd1 | cmnd2 | ...
	cmnd_qntt = count_cmnds(words);
	list = malloc(sizeof(t_cmnd *) * (cmnd_qntt + 1));
	// cmnd node of type t_cmnd
	cmnd_node = malloc(sizeof(t_cmnd));
	if (cmnd_node == NULL || list == NULL)
	{
		// add free()
		exit(1);
	}
	set_to_zero(cmnd_node);
	setup_cmnd_node(cmnd_node, words, cmnd_qntt, list, 0);
	return (list);
}
