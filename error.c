/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:53 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 16:11:27 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	error(int i, char *str)
{
	if (i == 1)
		write(2, "Invalid Input\n", 15);
	else if (i == 2)
		write(2, "not a valid identifier\n", 24);
	else if (i == 3)
		printf("Malloc error, exiting minishell\n");
	else
		printf("%s\n", str);
}
