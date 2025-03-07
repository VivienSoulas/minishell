/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:19:14 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/07 10:34:13 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char					**ft_split(const char *s, char c);
static size_t			count_words(const char *s, char c);
static int				filling(char **final_array, const char *s, char c);
static int				create_malloc(char **final_array, size_t len, int i);

// int	main(void)
// {
// 	char	s [] = "hello!";
// 	char	**new_array;
// 	char	c = ' ';
// 	int		i;

// 	i = 0;
// 	new_array = ft_split(s, c);
// 	if (!new_array)
// 		return (1);
// 	while (new_array[i])
// 	{
// 		printf("%s.\n", new_array[i]);
// 		free(new_array[i]);  // Free each individual substring
// 		i++;
// 	}
// 	free(new_array);
// 	return (0);
// }

char	**ft_split(const char *s, char c)
{
	size_t	words;
	char	**final_array;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	final_array = (char **) malloc ((words + 1) * sizeof(char *));
	if (!final_array)
		return (NULL);
	final_array[words] = NULL;
	if (filling(final_array, s, c) == 1)
	{
		return (NULL);
	}
	return (final_array);
}

static size_t	count_words(const char *s, char c)
{
	size_t	word;
	int		flag;

	word = 0;
	flag = 0;
	while (*s)
	{
		flag = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			if (!flag)
			{
				word++;
				flag = 1;
			}
			s++;
		}
	}
	return (word);
}

static int	filling(char **final_array, const char *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (create_malloc(final_array, len + 1, i) == 1)
				return (1);
			ft_strlcpy(final_array[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

static int	create_malloc(char **final_array, size_t len, int i)
{
	final_array[i] = (char *) malloc (len * sizeof(char));
	if (!final_array[i])
	{
		while (i >= 0)
		{
			free(final_array[i]);
			i--;
		}
		free(final_array);
		return (1);
	}
	return (0);
}
