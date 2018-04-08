/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:29:20 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/01 19:29:21 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

#define IS_DIGIT(c)	(c > 47 && c < 58) ? 1 : 0

int 	if_room(char *line, int i)
{
	//	printf("%sROOM: [%s]%s\n", GREEN, line, NORMAL);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	//	printf("1 line[%d]: [%c]\n", i, line[i]);
	if (line[i] == '-')
		i++;
	while (IS_DIGIT(line[i]))
		i++;
	//	printf("2 line[%d]: [%c]\n", i, line[i]);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] == '-')
		i++;
	while (IS_DIGIT(line[i]))
		i++;
	//	printf("3 line[%d]: [%c]\n", i, line[i]);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

void	rooms(t_file *file)
{
	t_room *room;
	int i;
	
	i = 0;
	
	while (gnl(file) != 0)
	{
		//		printf("ROOOOOMS1!\n");
		comment_command(file);
		room = (t_room *)malloc(sizeof(t_room));
		printf("%s[%s] room: %p%s\n", RED, file->line, &room, NORMAL);
		if (if_room(file->line, 0) == 0)
			break;
		room->name = get_name(file->line);
		room->weight = 0;
		room->next = NULL;
		room->open = 1;
		room->path = -1;
		file->nb_rooms++;
//		printf("%sROOMS: %p | ROOM TO ASIGN: %p%s\n", MAGNETA, ROOMS, &room, NORMAL);
		(ROOMS)[i++] = room;
		
	}
	printf("ROOMS: %d\n", file->nb_rooms);
}
