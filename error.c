/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:53 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 13:51:46 by jdavtian         ###   ########.fr       */
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
	else
		printf("%s\n", str);
}
