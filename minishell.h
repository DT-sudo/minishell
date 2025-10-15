/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/15 20:14:51 by dt               ###   ########.fr       */
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
	TOKEN_WORD,    // 0 // word: comands, flags
	TOKEN_PIPE,    // 1  // |
	TOKEN_RDR_IN,  // 2  // <
	TOKEN_RDR_OUT, // 3  // >
	TOKEN_APPND,   // 4  // >>
	TOKEN_HERE,    // 5  // <<
	TOKEN_COMPLEX  // 6  // "words"as'that'
}					token_type_t;

// cmnds structure
typedef struct s_cmnd
{
	char **argv;              // actuall argv[] that excve would work with
	char **full_argv;         // every argv for 1 command node
	token_type_t **argv_type; //  every argv type for 1 command node
	struct s_rdrs *rdrs;      // linked list of redirs for every command node
	bool rdr_in;              // <
	bool rdr_out;             // >
	bool appnd;               // >>
	bool heredoc;             // <<
	bool			pipe;
	struct s_cmnd	*next;
}					t_cmnd;

// input tokens
typedef struct s_input
{
	token_type_t	type;
	char			*word;
	struct s_input	*next;
}					t_input;

// redirs linked list
typedef struct s_rdrs
{
	token_type_t	redir_type;
	char			*filename;
	struct s_rdrs	*next;
}					t_rdrs;

typedef struct s_quote_state
{
	char			type;
	int				inquotes;
	int				closed;
	int				new_pair;
}					t_quote_state;

typedef struct s_xtnd
{
	int				len_dif;
	int				og_len;
	char			*new;
	struct s_xtnd	*next;
}					t_xtnd;

// length type and quote type for every token
typedef struct s_len_type_qts
{
	int				len;
	int				type;
	int				qts;
}					t_len_type_qts;

// envar var
typedef struct s_env
{
	char			*key;
	char			*value;
	int				new_len;
	struct s_env	*next;
}					t_env;

// creat_cmnd_list.c
t_input				*move_ptr_cmnd(t_input *next_cmnd);
void				set_apnd_hered_pipe(t_cmnd *node);
void				do_rdrs(t_cmnd *node);
t_cmnd				*setup_cmnd_node(t_cmnd *node, t_input *next_cmnd);
t_cmnd				*creat_cmnd_ls(t_input *words);

// cmnd_list_utils.c
void				set_to_zero(t_cmnd *cmnd_node);
int					count_cmnds(t_input *words);
int					count_cmnd_len(t_input *words);
int					count_cmnd_len_argv(t_input *words);
void				do_cmnd_array(t_input *words, t_cmnd *node, int size);
void				do_full_cmnd_array(t_input *words, t_cmnd *node, int size);
void				do_cmnd_array_type(t_input *words, t_cmnd *node, int size);

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
t_input				*do_node(t_len_type_qts *ltq, char *input);
t_input				*tokenize(t_input *words, char *input);
int					creat_tokenz(char *input, t_input **words);
void				add_node(t_input **words, t_input *new_word);

// tokenizer_utils.c
t_len_type_qts		*tk_in_here(char *input, t_len_type_qts *ltq);
t_len_type_qts		*tk_out_appnd(char *input, t_len_type_qts *ltq);
t_len_type_qts		*tk_pipe(char *input, t_len_type_qts *ltq);

// tokenizer_utils_2.c
t_len_type_qts		*tk_word(char *input, t_len_type_qts *ltq);
int					calc_len(t_input *new_word);
t_quote_state		*dtct_inquotes(char cr);
int					is_complex_wrd(t_len_type_qts *ltq, char *input);

// do_env_array.c
char				*strjoin_modified(char const *s1, char const *s2);
char				**do_env_array(t_env *env, int size);
int					count_env_ls(t_env *env);

// utils.c
void				ft_clean(t_input *words, char *input);
size_t				ft_strlenn(const char *s);

// dollar_list.c

void				reset_state_sttc(t_quote_state *state);
int					env_cmp(const char *key, const char *input);
t_xtnd				*xtnd_env(char *input, t_env **env);
int					calc_og(char *input);
void				connect_nodes(t_xtnd **head, t_xtnd *node);
t_xtnd				*crt_xtnd_ls(char *input, t_env **env);
int					calc_len_dif(t_xtnd *head);
void				put_value(char *new_input, t_xtnd *ls, int n);
char				*dollar_extend(char *input, t_env **env);

// echo_command_implementation.c
int					echo_command_implementation(t_cmnd **cmnd_ls, t_env **env);

// what_command.c
bool				is_command_buildin(char **input);
int					which_buildin_command(t_cmnd *cmnd, t_env **my_env,
						char **array_env);
void				what_command(t_cmnd **cmnd_ls, t_env **my_env,
						char **array_env);

// pwd_command_implementation.c
int					pwd_command_implementation(t_env *my_env);

// cd_command_implementation.c
int					cd_command_implementation(char **input, t_env *my_env);

// testing help_file.c
t_input				*initialize_command(void);

// cd
int					only_cd(char **input, t_env *env);
int					standard_cd(char **input, t_env *env);
int					previous_dir(char **input, t_env *env);

// export
char				**bubble_sort(char **array, int size);
int					only_export(char **input, t_env *env);

int					other_commands_implementation(char **input, t_env **env);
char				*ft_strjoin_free(char *s1, const char *s2);
char				**env_list_to_envp(t_env *env);

// env
t_env				*env_init(char **envp);
void				print_my_env(t_env *env);

// Updated function declarations
int					export_command_implementation(char **input, t_env **env,
						char **array_env);
int					unset_command_implementation(t_env **env, char **input);

// signal.c
void				handler_sig_int(int sig);
void				handler_sig_quit(int sig);
int					exit_func(void);
void				init_signals(void);

// // parsing.c
// t_input				*make_word(t_input *words, char *input);

#endif