/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 20:29:20 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/01 20:29:22 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	error(int errno)
{
	if (errno == 1)
		printf("ERROR: INVALID NUMBER/FORMAT/LACK OF ANTS\n");
	else if (errno == 2)
		printf("ERROR: NO START OR NO END\n");
	else if (errno == 3)
		printf("ERROR: WRONG COMMAND FORMAT/PLACEMENT\n");
	else if (errno == 4)
		printf("ERROR: EMPTY FILE\n");
	else if (errno == 5)
		printf("ERROR: NO PATHS\n");
	else if (errno == 6)
		printf("ERROR: IDK WHAT IT CHECKS LOL\n");
	else if (errno == 7)
		printf("ERROR: WRONG FILE FORMAT\n");
	else if (errno == 8)
		printf("ERROR: UNKNOWN ROOM\n");
	exit (0);
}

