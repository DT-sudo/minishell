/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:41:29 by dt                #+#    #+#             */
/*   Updated: 2025/10/19 20:51:09 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_len_type_qts	*tk_out_appnd(char *input, t_len_type_qts *ltq)
{
	char	*tmp;

	tmp = input;
	ltq->len = 1;
	ltq->qts = 0;
	ltq->type = TOKEN_RDR_OUT;
	if (*(++tmp) == '>')
	{
		ltq->len += 1;
		ltq->type = TOKEN_APPND;
	}
	return (ltq);
}

t_len_type_qts	*tk_in_here(char *input, t_len_type_qts *ltq)
{
	char	*tmp;

	tmp = input;
	ltq->len = 1;
	ltq->qts = 0;
	ltq->type = TOKEN_RDR_IN;
	if (*(++tmp) == '<')
	{
		ltq->len += 1;
		ltq->type = TOKEN_HERE;
	}
	return (ltq);
}

t_len_type_qts	*tk_pipe(char *input, t_len_type_qts *ltq)
{
	ltq->len = 1;
	ltq->type = TOKEN_PIPE;
	ltq->qts = 0;
	return (ltq);
}
