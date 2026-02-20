/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 01:07:09 by leauvray          #+#    #+#             */
/*   Updated: 2026/02/12 02:00:00 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipes(t_token *token, int token_count)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (i < token_count)
	{
		if (token[i].type == TOKN_PIPE)
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

static int	find_pipe_index(t_token *token, int start, int token_count)
{
	int	i;

	i = start;
	while (i < token_count && token[i].type != TOKN_PIPE)
		i++;
	return (i);
}

static void	fill_cmd_array(t_token *token, int token_count, t_cmd **cmd_array)
{
	int	i;
	int	cmd_idx;
	int	start;
	int	end;

	cmd_idx = 0;
	start = 0;
	i = 0;
	while (i < token_count)
	{
		end = find_pipe_index(token, start, token_count);
		cmd_array[cmd_idx] = parse_tokens(token + start, end - start);
		if (!cmd_array[cmd_idx])
			return ;
		cmd_idx++;
		start = end + 1;
		i = start;
	}
	cmd_array[cmd_idx] = NULL;
}

t_cmd	**parse_pipeline(t_token *token, int token_count)
{
	t_cmd	**cmd_array;
	int		pipe_count;
	int		cmd_count;

	if (!token || token_count < 1)
		return (NULL);
	pipe_count = count_pipes(token, token_count);
	cmd_count = pipe_count + 1;
	cmd_array = malloc(sizeof(t_cmd *) * (cmd_count + 1));
	if (!cmd_array)
		return (NULL);
	fill_cmd_array(token, token_count, cmd_array);
	return (cmd_array);
}
