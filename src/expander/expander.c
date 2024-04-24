/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/24 16:13:51 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_quotes_status(t_token *tokens)
{
	t_token	*temp;
	int		in_single_quotes;
	int		in_double_quotes;

	temp = tokens;

	while (temp)
	{
		in_single_quotes = 0;
		in_double_quotes = 0;
		if (temp->value[0] == S_QUOTE && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (temp->value[0] == D_QUOTE && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (in_single_quotes)
			temp->quotes_status = SQUOTED;
		else if (in_double_quotes)
			temp->quotes_status = DQUOTED;
		else
			temp->quotes_status = NONE;
		temp = temp->next;
	}
}

int	expander(t_token *tokens, t_shell *shell)
{
	t_token	*temp;
	int		i;

	(void)shell;
	temp = tokens;
	set_quotes_status(temp);
	while (temp)
	{
		// printf("TOKEN[%d]\ntemp->value: %s\ntemp->type: %d\ntemp->quotes: %d\n",
		// 	temp->id, temp->value, temp->type, temp->quotes_status);
		if (temp->type == WORD || temp->type == FILENAME)
		{
			i = 0;
			while (temp->value[i])
			{
				if (temp->value[i] == '$' && temp->value[i + 1] != '\0'
					&& !char_is_separator(temp->value[i + 1])
					&& (temp->quotes_status == NONE
						|| temp->quotes_status == DQUOTED))
					replace_with_expansion(&temp, shell);
				i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}
