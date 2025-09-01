/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:12:01 by dt                #+#    #+#             */
/*   Updated: 2025/08/26 14:44:10 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum
{
	TOKEN_WORD,    // 1 // word: comands, flags
	TOKEN_SG_Q,    // 2  // ''
	TOKEN_DB_Q,    // 3  // ""
	TOKEN_PIPE,    // 4  // |
	TOKEN_RDR_IN,  // 5  // <
	TOKEN_RDR_OUT, // 6  // >
	TOKEN_APPND,   // 7  // >>
	TOKEN_HERE,    // 8  // <<
	TOKEN_NVP      // 9  // $
}					token_type_t;

typedef struct s_input
{
	token_type_t	type;
	struct s_input	*next;
	char			*word;
}					t_input;

// validate_input.c
int					has_backslash(char *input);
int					has_simocolon(char *input);
int					has_double_and_or_pipe(char *input);
bool				validate_input(char *input);

// validate_input_2.c
int					find_sq(char *input, int *signl_q);
int					find_dq(char *input, int *double_q);
int					has_unclosed_quotes(char *input);
bool				drop_false(char *error_message);

// tokenizer.c
int					add_node(t_input **words, t_input *new_word, int tk_len);
t_input				*do_node(int start_end[], char *input);
int					creat_tokenz(char *input, t_input **words, int tk_len);
t_input				*tokenize(t_input *words, char *input);
int					tk_len_calc_len(t_input *new_word, int tk_len);

// tokenizer_utils_2.c
int					calc_len(t_input *new_word);
int					*tk_word(char *input, int res[3]);
int					*tk_s_quotes(char *input, int res[3]);
int					*tk_d_quotes(char *input, int res[3]);

// tokenizer_utils.c
int					*tk_in_here(char *input, int res[3]);
int					*tk_out_appnd(char *input, int res[3]);
int					*tk_pipe(char *input, int res[3]);
int					*tk_envp_v(char *input, int res[3]);

// utils.c
size_t				ft_strlen(const char *s);

#endif