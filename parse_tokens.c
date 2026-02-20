/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 01:41:05 by leauvray          #+#    #+#             */
/*   Updated: 2026/02/12 01:33:34 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	return (cmd);
}

void	allocate_args(t_cmd *cmd, int token_count)
{
	cmd->args = ft_calloc(token_count + 1, sizeof(char *));
	if (!cmd->args)
		return ;
}

void	parse_args(t_token *token, int token_count, t_cmd *cmd)
{
	int	i;
	int	arg_idx;

	i = 1;
	arg_idx = 0;
	while (i < token_count && token[i].type != TOKN_PIPE)
	{
		if (token[i].type == TOKN_WORD)
		{
			cmd->args[arg_idx++] = token[i].value;
		}
		else if (token[i].type == TOKN_REDIR_IN
			|| token[i].type == TOKN_REDIR_OUT || token[i].type == TOKN_APPEND)
		{
			i++;
		}
		i++;
	}
}

void	parse_redirections(t_token *token, int token_count, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < token_count && token[i].type != TOKN_PIPE)
	{
		if (token[i].type == TOKN_REDIR_IN && i + 1 < token_count)
		{
			cmd->input_file = token[i + 1].value;
			i += 2;
		}
		else if (token[i].type == TOKN_REDIR_OUT && i + 1 < token_count)
		{
			cmd->output_file = token[i + 1].value;
			cmd->append = 0;
			i += 2;
		}
		else if (token[i].type == TOKN_APPEND && i + 1 < token_count)
		{
			cmd->output_file = token[i + 1].value;
			cmd->append = 1;
			i += 2;
		}
		else
			i++;
	}
}

t_cmd	*parse_tokens(t_token *token, int token_count)
{
	t_cmd	*cmd;

	if (!token || token_count < 1 || token[0].type != TOKN_WORD)
		return (NULL);
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd->command = token[0].value;
	allocate_args(cmd, token_count);
	if (!cmd->args)
		return (NULL);
	parse_args(token, token_count, cmd);
	parse_redirections(token, token_count, cmd);
	return (cmd);
}
