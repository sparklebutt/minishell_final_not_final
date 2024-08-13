/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/08/13 19:15:07 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ this is baisicicaly split excepet it ignores the delimeter inside quotes.
quotes signify a full string therefore we need any and all spaces inside them ~~*/
static int	fancy_strlen(char const *s, char c, int i)
{
	int test;
	test = 0;
	while (s[i] && s[i] != c) // && is_char_redirect(s[i]) == 0)
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		i++;
	}
//	test = is_char_redirect(s[i]);
//	printf("show me test = %d\n", test);
//	if (test > 0)
//		return (test);
//	printf("show me i = %d\n", i);
	return (i);
}

/*~~ leave commented code in here, i will finish this soon, it got a bit late, attempt
to increase word count based on having no spaces but having redirects non the less, 
will add pipes also~~*/
size_t	total_words_c(char const *s, char c)
{
	int	words;
	int	i;
	int test;

	test = 0;
	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (s[i] == '"' && i++)
			{
				while (s[i] && s[i] != '"')
					i++;
			}
			else if (s[i] == '\'')
			{
				while (s[i] && s[i] != '\'' && i++)
					i++;
			}
			i++;
		}
//		else if (is_char_redirect(s[i]) > 0)
//		{
//			words++;
//			i += is_char_redirect(s[i]);//fancy_strlen(s, c, i) - i;
//		}
		else if (s[i] != c)
		{
			words++;
			i += fancy_strlen(s, c, i) - i;
		}	
	}
//	printf("show me word count = %d\n", words);
	return (words);
}

static char	**free_array_if(char **array)
{
	int	word;

	word = 0;
	while (array[word] != NULL)
		free(array[word++]);
	free(array);
	return (NULL);
}
/*~~ split string but do not remove spaces if inside quotes to input into tokesn array
we are missing special cases where there are no spaces yet special symbols do exist
eg hello>world>spagett OR echo hello>banana_file|cat>spaghetti, total_words_c will also have
to take all of this into consideration, due to atleast 1 extra use of the fucntion~~*/
char	**ft_split_adv(char const *s, char c)
{
	size_t	i;
	char	**array;
	size_t		word;
	int		word_len;

	i = 0;
	word = 0;
	array = (char **)ft_calloc(sizeof(char *), (total_words_c(s, c) + 1));
	if (!s || !array)
		return (NULL);
	while (s[i] != '\0' && word < total_words_c(s, c))
	{
		while (s[i] == c)
			i++;
		word_len = fancy_strlen(s, c, i) - i;
		array[word] = ft_substr(s, i, word_len);
		if (array[word] == NULL)
			return (free_array_if(array));
		i += ft_strlen(array[word]);
		word++;
	}
	array[word] = NULL;
	return (array);
}
