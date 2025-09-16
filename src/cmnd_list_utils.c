/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:31:02 by dt                #+#    #+#             */
/*   Updated: 2025/09/11 17:27:29 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_to_zero(t_cmnd *cmnd_node)
{
	cmnd_node->argv = NULL;
	cmnd_node->argv_type = NULL;
	cmnd_node->rd_out_filename = NULL;
	cmnd_node->rd_in_filename = NULL;
	cmnd_node->appnd = false;
	cmnd_node->heredoc = false;
	cmnd_node->next = NULL;
}

// counts how many commands within one input by  '|'
int	count_cmnds(t_input *words)
{
	int		i;
	t_input	*tmp;

	i = 1;
	if (words == NULL)
		return (0);
	tmp = words;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

// counts how many tokens within one command
int	count_cmnd_len(t_input *words)
{
	int		i;
	t_input	*tmp;

	i = 0;
	if (words == NULL)
		return (0);
	tmp = words;
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// SUS
char	**do_input_array(t_input *input, int size)
{
	int		i;
	char	**res;
	t_input	*tmp;

	if (input == NULL)
		return (NULL);
	i = 0;
	tmp = input;
	res = malloc(sizeof(char *) * size + 1);
	while (tmp != NULL && i < size)
	{	
		res[i++] = tmp->word;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

// returns malloced array of one command
void	do_cmnd_array(t_input *words, t_cmnd *node, int size)
{
	int		i;
	t_input	*tmp;
	char	**res;

	if (words == NULL)
		return;
	i = 0;
	tmp = words;
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		exit(1);
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		res[i++] = tmp->word;
		tmp = tmp->next;
	}
	res[i] = NULL;
	node->argv = res;
}

// makes array of each token type of every cmnd token
void	do_cmnd_array_type(t_input *words, t_cmnd *node, int size)
{
	int		i;
	t_input	*tmp;
	token_type_t	**res_type;

	i = 0;
	if (words == NULL)
		return;
	tmp = words;
	res_type = malloc(sizeof(token_type_t *) * (size + 1));
	if (res_type == NULL)
		exit(1);
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		res_type[i++] = &tmp->type;
		tmp = tmp->next;
	}
	res_type[i] = NULL;
	node->argv_type = res_type;
}
