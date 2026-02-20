/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:47:58 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/13 10:15:49 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	int		i;

	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		else if (input[0] != '\0' || ft_strlen(input) > 0)
		{
			add_history(input);
			tokens = tokenizer(input);
			if (!tokens->code)
			{
				i = 0;
				while (tokens->args[i])
				{
					printf("Token[%d] : [%s]\n", tokens->value[i], tokens->args[i]);
					i++;
				}
				free_tab(tokens->args);
				free(tokens->value);
			}
			else
				printf("Error: %d", tokens->code);
			free(tokens);
		}
		free(input);
	}
	return (0);
}
