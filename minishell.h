/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/01 20:05:30 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/libft/libft.h"
# include "libs/libftprintf/ft_printf.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

extern int			exit_status;

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

// input tokens
typedef struct s_input
{
	token_type_t	type;
	struct s_input	*next;
	char			*word;
}					t_input;

// envar var
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

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

// tokenizer_utils.c
int					*tk_in_here(char *input, int res[3]);
int					*tk_out_appnd(char *input, int res[3]);
int					*tk_pipe(char *input, int res[3]);
int					*tk_envp_v(char *input, int res[3]);

// tokenizer_utils_2.c
int					calc_len(t_input *new_word);
int					*tk_word(char *input, int res[3]);
int					*tk_s_quotes(char *input, int res[3]);
int					*tk_d_quotes(char *input, int res[3]);

// do_array.c
char				*strjoin_modified(char const *s1, char const *s2);
int					count_list_input(t_input *input);
int					count_list_env(t_env *env);
char				**do_input_array(t_input *input, int size);
char				**do_env_array(t_env *env, int size);

// utils.c
size_t				ft_strlen(const char *s);

// what_command.c
bool				is_command_buildin(char **input);
void				what_command(char **input, t_env *my_env, char **array_env);
int				echo_command_implementation(char **input);
int 				pwd_command_implementation(t_env *my_env);
// int 				export_command_implementation(char **input);
// int 				unset_command_implementation(char **input);
int 				cd_command_implementation(char **input, t_env *my_env);
// void 				exit_command_implementation(t_env *my_env);

//testing help_file.c
t_input *initialize_command();

//cd
int	only_cd(char **input, t_env *env);
int standard_cd(char **input, t_env *env);
int previous_dir(char **input, t_env *env);

//export
int export_command_implementation(char **input,  t_env *env, char **array_env);
char **bubble_sort(char **array, int size);
int only_export(char **input, char **array_env);



int other_commands_implementation(char **input, t_env *env);
char *ft_strjoin_free(char *s1, const char *s2);
char	**env_list_to_envp(t_env *env);


// env
t_env				*env_init(char **envp);
void				print_my_env(t_env *env);

// // parsing.c
// t_input				*make_word(t_input *words, char *input);

#endif