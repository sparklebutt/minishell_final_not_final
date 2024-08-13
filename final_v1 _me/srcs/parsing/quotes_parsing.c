/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:55:36 by araveala          #+#    #+#             */
/*   Updated: 2024/08/13 18:34:51 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_quotes(t_tokens *tokens, int quote_count, int i, int *x)
{
	char	c;

	c = 0;
	if (tokens->quote == 1)
		c = '\'';
	else if (tokens->quote == 2)
		c = '"';
	(*x)++;
	quote_count += 1;
	if (tokens->args[i][*x] == c)
		quote_count += 1;
	while (tokens->args[i][*x] != '\0' && tokens->args[i][*x] != c)
	{
		(*x)++;
		if (tokens->args[i][*x] == c)
			quote_count += 1;
	}
	return (quote_count);
}

int	check_open_quotes(t_tokens *tokens, int s_quote_count, int d_quote_count)
{
	int	x;
	int	i;

	i = -1;
	while (tokens->args[++i])
	{
		x = 0;
		while (tokens->args[i][x] != '\0')
		{
			if (tokens->args[i][x] == '\'')
			{
				tokens->quote = 1;
				s_quote_count = loop_quotes(tokens, s_quote_count, i, &x);
			}
			else if (tokens->args[i][x] == '"')
			{
				tokens->quote = 2;
				d_quote_count = loop_quotes(tokens, d_quote_count, i, &x);
			}
			x++;
		}
		if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
			return (-1);
	}
	return (1);
}

int	count_new_len(char *string)
{
	int	x;
	int	len;

	x = -1;
	len = 0;
	while (x++ && string[x] != '\0')
	{
		if (string[x] == '\'')
		{
			x++;
			while (string[x] != '\'' && x++)
				len++;
			len--;
		}
		else if (string[x] == '"')
		{
			x++;
			while (string[x] != '"' && x++)
				len++;
			len--;
		}
		len++;
	}
	return (len);
}

/*~~ added an extra check so that $symbol wuld not be copied over if its outside quotes,
need to check that this is ok for other cases but eg $"USER" should not print the $symbol
may need to add other symbols it is commenetd out due to causing problems with eg $HOME""
a fucntion is required to handle these cases , loop_quotes could potentially be re-utalized~~*/
char	*clean_quotes(char *string, int len, int x, int y)
{
	char	*new;

	new = NULL;
	new = ft_calloc(len + 1, 1);
	if (new == NULL)
		return (NULL);
	while (x <= len)
	{
		if (string[x] == '\'')
		{
			x++;
			while (string[x] != '\'')
				new[y++] = string[x++];
		}
		else if (string[x] == '"')
		{
			x++;
			while (string[x] != '"')
				new[y++] = string[x++];
		}
		if (string[x] != '\'' && string[x] != '"') // && string[x] != '$')
			new[y++] = string[x];
		x++;	
	}
	return (*&new);
}
