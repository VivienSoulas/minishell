/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:53 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:00:54 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	error(int i, char *str)
{
	if (i == 1)
		printf("Invalid Input\n");
	else if (i == 2)
		printf("`%s' not a valid identifier\n", str);
	else if (i == 3)
		printf("Malloc error, exiting minishell\n");
}
