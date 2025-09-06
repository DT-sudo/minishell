/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmnd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:44 by dt                #+#    #+#             */
/*   Updated: 2025/09/06 18:44:14 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns pointer to the next command from t_input words
t_input	*move_ptr_cmnd(t_input *next_cmnd)
{
	if (next_cmnd == NULL)
		exit(1);
	while (next_cmnd->type != TOKEN_PIPE && next_cmnd != 0)
		next_cmnd = next_cmnd->next;
	if (next_cmnd->type == TOKEN_PIPE)
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
		if (node->argv_type[i] == TOKEN_APPND)
			node->appnd = true;
		else if (node->argv_type[i] == TOKEN_HERE)
			node->heredoc = true;
		else if (node->argv_type[i] == TOKEN_PIPE)
			node->has_pipe = true;
		i++;
	}
}

t_cmnd	*list_nodes(t_cmnd *node, t_cmnd **list, int cmnd_qntt)
{
	int			j;
	static int	i;

	j = 0;
	if (node == NULL)
		return NULL;
	list[i] = node;
	if (i == cmnd_qntt)
	{
		while (j < i)
		{
			list[j]->next = list[j + 1];
			j++;
		}
		list[j] = NULL;
		i = 0;
	}
	i++;
}

void	set_filename(t_cmnd *node)
{
	int	i;

	i = 0;
	while (!(*(node->argv_type[i]) >= TOKEN_RDR_IN
			&& *(node->argv_type[i]) <= TOKEN_HERE) && *(node->argv_type[i]) != NULL)
		i++;
	if ((*(node->argv_type[i]) == 4 || *(node->argv_type[i]) == 7)
		&& *(node->argv_type[i]) != NULL)
		node->rd_in_filename = node->argv[i];
	else if ((*(node->argv_type[i]) == 5 || *(node->argv_type[i]) == 6)
		&& *(node->argv_type[i]) != NULL)
		node->rd_out_filename = node->argv[i];
}

// setup of each cmnd node and list them together
t_cmnd	*setup_cmnd_node(t_cmnd *node, t_input *next_cmnd, int cmnd_qntt,
		t_cmnd *list)
{
	static int	c;
	t_cmnd		*new_node;

	do_cmnd_array(next_cmnd, node, count_cmnd_len(next_cmnd));
	do_cmnd_array_type(next_cmnd, node, count_cmnd_len(next_cmnd));
	set_apnd_hered_pipe(node);
	set_filename(node);
	list_nodes(node, &list, cmnd_qntt);
	while (c++ < cmnd_qntt && cmnd_qntt > 1)
	{
		new_node = malloc(sizeof(t_cmnd));
		if (new_node == NULL)
		{
			// add free()
			exit(0);
		}
		set_to_zero(new_node);
		new_node = setup_cmnd_node(new_node, move_ptr_cmnd(next_cmnd),
				cmnd_qntt, list);
	}
	c = 0;
	return (node);
}

t_cmnd	*creat_cmnd_list(t_input *words, int size)
{
	int		i;
	int		cmnd_qntt;
	t_cmnd	*cmnd_node;
	t_cmnd	*list;

	if (words == NULL)
		return (NULL);
	i = 0;
	cmnd_qntt = count_cmnds(words);
	list = malloc(sizeof(t_cmnd *) * (cmnd_qntt + 1));
	cmnd_node = malloc(sizeof(t_cmnd));
	if (cmnd_node == NULL || list == NULL)
	{
		// add free()
		exit(1);
	}
	set_to_zero(cmnd_node);
	setup_cmnd_node(cmnd_node, words, cmnd_qntt, list);
	return (cmnd_node);
}
