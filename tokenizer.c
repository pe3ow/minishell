/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:42:49 by leauvray          #+#    #+#             */
/*   Updated: 2026/02/13 11:08:34 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && ft_strlen(str) == 1)
			return (TOKN_PIPE);
		else if (str[i] == '>' && ft_strlen(str) == 1)
			return (TOKN_REDIR_OUT);
		else if (str[i] == '<' && ft_strlen(str) == 1)
			return (TOKN_REDIR_IN);
		else if (str[i] == '>' && str[i + 1] == '>' && ft_strlen(str) == 2)
			return (TOKN_APPEND);
		else if (str[i] == '<' && str[i + 1] == '<' && ft_strlen(str) == 2)
			return (TOKN_HEREDOC);
		else
			return (TOKN_WORD);
		i++;
	}
	return (0);
}

static char	*extract_word(char *s, int *i)
{
	int		len;
	char	quote;
	char	*word;

	len = 0;
	word = malloc(10000);
	if (!word)
		return (NULL);
	while (s[*i] && !ft_isspace(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			quote = s[(*i)++];
			while (s[*i] && s[*i] != quote)
				word[len++] = s[(*i)++];
			if (s[*i] == quote)
				(*i)++;
		}
		else
			word[len++] = s[(*i)++];
	}
	word[len] = '\0';
	return (word);
}

static char	**init_argv(char *input)
{
	char	**argv;
	int		i;
	int		j;

	j = 0;
	i = 0;
	argv = malloc(sizeof(char *) * (count_words(input) + 1));
	if (!argv)
		return (NULL);
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		argv[j] = extract_word(input, &i);
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

t_token	*tokenizer(char *input)
{
	int				i;
	t_token			*token;
	char			**av;

	i = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->code = check_quotes(input);
	if (token->code)
		return (token);
	av = init_argv(input);
	token->args = malloc(sizeof(char *) * (ft_tablen((const char **)av) + 1));
	token->value = malloc(sizeof(int) * (ft_tablen((const char **)av) + 1));
	if (!token->args || !token->value)
		return (NULL);
	while (av[i])
	{
		token->value[i] = check_type(av[i]);
		token->args[i] = ft_strdup(av[i]);
		i++;
	}
	token->args[i] = NULL;
	return (token);
}
