/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/07 23:54:17 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_state_sttc(t_quote_state *state)
{
	if (!state)
		return ;
	state->closed = 0;
	state->inquotes = 0;
	state->new_pair = 0;
	state->type = '\0';
}

// calcs length to add to OG_input lenght for extented *new_input
int	calc_len_dif(t_xtnd *head)
{
	t_xtnd	*tmp;
	int		len_dif;

	len_dif = 0;
	if (!head)
		exit(33);
	tmp = head;
	while (tmp != NULL)
	{
		len_dif += tmp->len_dif;
		tmp = tmp->next;
	}
	return (len_dif);
}

//ok
// calcs lenght of OG $ENV accurance within original input
int	calc_og(char *input)
{
	int		i;

	i = 1;
	while (*input)
	{
		if (!(*input >= 48 && *input <= 57 || *input >= 65
				&& *input <= 90 || *input >= 97 && *input <= 122
				|| *input == 95))
			break ;
		input++;
		i++;
	}
	return (i);
}

// connects nodes of t_xtnd linked ls
void	connect_nodes(t_xtnd **head, t_xtnd *node)
{
	t_xtnd *tmp;

	tmp = *head;
	if (!node || !head)
		exit(22);
	if (*head == NULL)
	{
		*head = node;
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

//ok
// finds out if $ENV has value
int	env_cmp(const char *key, const char *input)
{
	while (*key && (*key == *input))
	{
		input++;
		key++;
	}
	//case when $ENV is dellimited with some other chars except sp/tab 
	if (*key == '\0')
	{
		if (!(*input >= 48 && *input <= 57 || *input >= 65
				&& *input <= 90 || *input >= 97 && *input <= 122
				|| *input == 95))
			return (1);
	}
	return (0);
}

// creats t_xtnd node
t_xtnd	*xtnd_env(char *input, t_env **env)
{
	t_xtnd	*node;
	t_env	*current;

	current = *env;
	node = malloc(sizeof(t_xtnd));
	if (!node)
		exit(2);
	node->new = NULL;
	node->next = NULL;
	node->og_len = 0;
	node->len_dif = 0;
	while (current)
	{
		if (env_cmp(current->key, input))
		{
			node->og_len = ft_strlen(current->key) + 1;
			node->new = ft_strdup(current->value);
			node->len_dif = ft_strlen(node->new) - node->og_len;
			return (node);
		}
		current = current->next;
	}
	return (node);
}

void	put_value(char *new_input, t_xtnd *ls, int n)
{
	int	x;

	x = 0;
	if (!new_input || !ls)
		exit(9);
	while (ls->new[x])
	{
		new_input[n + x] = ls->new[x];
		x++;
	}
}

// problem is here for now
// creats t_xtnd linked ls with data for $ENV extention
t_xtnd	*crt_xtnd_ls(char *input, t_env **env)
{
	t_quote_state	*state;
	t_xtnd			*xtnd_node;
	t_xtnd			*head;

	head = NULL;
	if (!input || !env)
		return (NULL);
	while (*input)
	{
		state = dtct_inquotes(*input);
		if (!state)
			exit(40);
		if (*input == '$' && *(input + 1) != '\0' && (state->type == '"'
				|| state->type == 0))
		{
			xtnd_node = xtnd_env(input + 1, env);
			if (!xtnd_node)
				exit(41);
			if (!xtnd_node->new)
			{
				xtnd_node->new = ft_strdup("");
				xtnd_node->og_len = calc_og(input + 1);
				xtnd_node->len_dif = ft_strlen(xtnd_node->new)
					- xtnd_node->og_len;
			}
			connect_nodes(&head, xtnd_node);
		}
		input++;
	}
	reset_state_sttc(state);
	return (head);
}

char	*dollar_extend(char *input, t_env **env)
{
	t_quote_state	*state;
	t_xtnd			*xtnds;
	char			*new_input;
	int				n;
	int				i;

	if (!input || !env)
		return (NULL);
	n = 0;
	i = 0;
	xtnds = crt_xtnd_ls(input, env);
	if (!xtnds)
		return (ft_strdup(input));
	new_input = malloc(sizeof(char) * (ft_strlen(input)
				+ calc_len_dif(xtnds) + 1));
	if (!new_input)
		return (ft_strdup(input));
	while (input[i])
	{
		state = dtct_inquotes(input[i]);
		if (input[i] == '$' && input[i + 1] && (state->type == '"'
				|| state->type == 0))
		{
			put_value(new_input, xtnds, n);
			n += ft_strlen(xtnds->new);
			i += xtnds->og_len;
			xtnds = xtnds->next;
		}
		else
			new_input[n++] = input[i++];
	}
	new_input[n] = '\0';
	reset_state_sttc(state);
	return (new_input);
}
