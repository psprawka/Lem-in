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
		printf("ERROR: WRONG COMMAND FORMAT OR PLACEMENT\n");
	else if (errno == 4)
		printf("ERROR: EMPTY FILE\n");
	else if (errno == 5)
		printf("ERROR: NO PATHS\n");
	else if (errno == 6)
		printf("ERROR: IDK WHAT IT CHECKS LOL\n");
	else if (errno == 7)
		printf("ERROR: WRONG FILE FORMAT\n");
	else if (errno == 8)
		printf("ERROR: UNKNOWN ROOM OR ROOM REPEATED\n");
	else if (errno == 9)
		printf("ERROR: ROOM LINKS TO ITSELF\n");
	else if (errno == 10)
		printf("ERROR: MULTIPLE STARTS OR ENDS\n");
	else if (errno == 11)
		printf("ERROR: NO ROOMS\n");
	else if (errno == 12)
		printf("ERROR: EMPTY LINE\n");
	exit (0);
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

void	rooms_exist(t_file *file, char *r1, char *r2)
{
	int i;
	int	rooms;
	
	i = 0;
	rooms = 0;
	while (i < file->nb_rooms)
	{
		if (ft_strcmp(ROOMS[i]->name, r1) == 0)
			rooms++;
		if (ft_strcmp(ROOMS[i]->name, r2) == 0)
			rooms++;
		i++;
	}
	if (rooms != 2)
		error(8);
	if (ft_strcmp(r1, r2) == 0)
		error(9);
}

