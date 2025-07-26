/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:12:01 by dt                #+#    #+#             */
/*   Updated: 2025/07/26 19:04:57 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

typedef enum{
    TOKEN_WORD, //0
    TOKEN_PIPE, //0
    TOKEN_REDIR_IN, //0
    TOKEN_REDIR_OUT, //0
} token_type_t;

typedef struct s_input
{
    //after parse_input type = "TOKEN_WORD/TOKEN_PIPE/TOKEN_REDIR_IN etc..."
    token_type_t    type;
	struct s_input	*next;
	char			*word;
} t_input;

//parsing.c
void	parse_input(t_input *words, char *input);
t_input	*make_word(t_input *words, char *input);

//utils.c
size_t	ft_strlen(const char *s);

#endif