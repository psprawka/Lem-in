/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 23:24:41 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/09 23:24:44 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	error(int errno)
{
	if (errno == 1)
		ft_printf("ERROR: INVALID NUMBER/FORMAT OF ANTS\n");
	else if (errno == 2)
		ft_printf("ERROR: NO START OR NO END\n");
	else if (errno == 3)
		ft_printf("ERROR: WRONG COMMAND FORMAT OR PLACEMENT\n");
	else if (errno == 4)
		ft_printf("ERROR: EMPTY FILE\n");
	else if (errno == 5)
		ft_printf("ERROR: NO PATHS\n");
	else if (errno == 6)
		ft_printf("ERROR: IDK WHAT IT CHECKS LOL\n");
	else if (errno == 7)
		ft_printf("ERROR: WRONG FILE FORMAT\n");
	else if (errno == 8)
		ft_printf("ERROR: UNKNOWN ROOM OR ROOM REPEATED\n");
	else if (errno == 9)
		ft_printf("ERROR: ROOM LINKS TO ITSELF\n");
	else if (errno == 10)
		ft_printf("ERROR: MULTIPLE STARTS OR ENDS\n");
	else if (errno == 11)
		ft_printf("ERROR: NO ROOMS\n");
	else if (errno == 12)
		ft_printf("ERROR: EMPTY LINE\n");
	exit(0);
}

char	*colorsfind(t_file *file, char *command)
{
	if (ft_strncmp(command, "##green", 7) == 0 && gnl(file))
		return (GREEN);
	if (ft_strncmp(command, "##red", 5) == 0 && gnl(file))
		return (RED);
	if (ft_strncmp(command, "##yellow", 8) == 0 && gnl(file))
		return (YELLOW);
	if (ft_strncmp(command, "##cyan", 6) == 0 && gnl(file))
		return (CYAN);
	if (ft_strncmp(command, "##blue", 6) == 0 && gnl(file))
		return (BLUE);
	if (ft_strncmp(command, "##magneta", 9) == 0 && gnl(file))
		return (MAGNETA);
	if (ft_strncmp(command, "##pink", 6) == 0 && gnl(file))
		return (PINK);
	if (ft_strncmp(command, "##orange", 8) == 0 && gnl(file))
		return (ORANGE);
	if (ft_strncmp(command, "##grey", 6) == 0 && gnl(file))
		return (GREY);
	if (ft_strncmp(command, "##maroon", 8) == 0 && gnl(file))
		return (MAROON);
	if (ft_strncmp(command, "##purple", 8) == 0 && gnl(file))
		return (PURPLE);
	return (NULL);
}
