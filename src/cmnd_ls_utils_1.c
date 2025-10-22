/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_ls_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:36:59 by dt                #+#    #+#             */
/*   Updated: 2025/10/23 00:52:51 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// chage to ft_strdup(tmp->word); for right free(t_input) work ??
// returns malloced array of one command
void	do_cmnd_array(t_input *words, t_cmnd *node, int size)
{
	t_input	*tmp;
	char	**res;
	int		i;

	if (words == NULL)
		return ;
	i = 0;
	tmp = words;
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		exit(1);
	while (tmp != NULL && tmp->type != TOKEN_PIPE)
	{
		if (!(tmp->type == TOKEN_RDR_IN || tmp->type == TOKEN_RDR_OUT
				|| tmp->type == TOKEN_APPND || tmp->type == TOKEN_HERE))
			res[i++] = tmp->word;
		else
			tmp = tmp->next;
		tmp = tmp->next;
	}
	res[i] = NULL;
	node->argv = res;
}

// returns malloced array of one command
// chage to ft_strdup(tmp->word); for right free(t_input) work
void	do_full_cmnd_array(t_input *words, t_cmnd *node, int size)
{
	int		i;
	t_input	*tmp;
	char	**res;

	if (words == NULL)
		return ;
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
	node->full_argv = res;
}

// makes array of each token type of every cmnd token
void	do_cmnd_array_type(t_input *words, t_cmnd *node, int size)
{
	int				i;
	t_input			*tmp;
	token_type_t	**res_type;

	i = 0;
	if (words == NULL)
		return ;
	tmp = words;
	res_type = malloc(sizeof(token_type_t *) * (size + 1));
	if (res_type == NULL)
		exit(1);
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			node->pipe = true;
			break ;
		}
		res_type[i++] = &tmp->type;
		tmp = tmp->next;
	}
	res_type[i] = NULL;
	node->argv_type = res_type;
}

void	set_apnd_hered_pipe(t_cmnd *node)
{
	int i;

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
