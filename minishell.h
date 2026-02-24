/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:35:23 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/24 19:33:02 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//====INCLUDE-HEADER====//
# include "Libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

//====INCLUDE-STRUCTURE====//

typedef struct s_env // structure pour stocker les variables d'environnement dans une liste chaînée
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef enum s_token_type
{
	TOKN_WORD,
	TOKN_PIPE,
	TOKN_REDIR_OUT,
	TOKN_REDIR_IN,
	TOKN_APPEND,
	TOKN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				code; // code d'erreur pour gere les quote et les doubles quotes
	char			*value;
	char			**args;
}					t_token;

typedef struct s_cmd
{
	char	*command;
	char	**args;
	char	*input_file;// NULL ou nom du fichier si <
	char	*output_file;// NULL ou nom du fichier si >
	int		append;// si = 0(>) ecrase si = 1 ajoute (>>)
						// ex : grep "error" < input.log > output.txt
}			t_cmd;

//====INCLUDE-FONCTION====//

//==utils==//
char		*ft_strljoin(char const *s1, int start, int end);
int			ft_isspace(int c);
void		free_tab(char **str_tab);
int			count_words(char *str);
int			check_quotes(char *str);
char		*get_env_value(t_env *env, char *key);
int			set_env(t_env **env, char *key, char *value);
//==tokenizer==//
t_token		*tokenizer(char *input);
//==parse==//
t_cmd		*parse_tokens(t_token *tokens, int token_count);
t_cmd		**parse_pipeline(t_token *tokens, int token_count);
char		**extract_args(t_token *tokens, int start, int end);
//==commands==//
int			cd(t_cmd *cmd, char **env);
int			pwd(void);
void		echo(char *str);
int			export(t_cmd *cmd, char **env);
int			unset(t_cmd *cmd, char **env);
int			builtin_exit(t_cmd *cmd, char **env);
int			env(t_cmd *cmd, char **env);
//==exec==//
int			monitor(t_cmd **cmd_array, t_token **args, char **envp);
int			exec_builtin(t_token **args, char *cmd);
int			exec_external(t_token **args, t_cmd *cmd, char **envp);

#endif