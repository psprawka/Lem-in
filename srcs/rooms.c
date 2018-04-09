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
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '-')
		i++;
	while (IS_DIGIT(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] == '-')
		i++;
	while (IS_DIGIT(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

void	rooms(t_file *file)
{
	t_room	*room;
	char	*color;
	int		i;
	
	i = 0;
	while (gnl(file) != 0)
	{
//		printf("%sBEFORE[%s] room: %p%s\n", RED, LINE, &room, NORMAL);
		color = comment_command(file);
		room = (t_room *)malloc(sizeof(t_room));
//		printf("%sAFTER[%s] room: %p%s\n", RED, LINE, &room, NORMAL);
		if (if_room(LINE, 0) == 0)
			break;
		room->name = get_name(LINE);
		room->weight = 0;
		room->next = NULL;
		room->color = color == NULL ? NORMAL : color;
		room->open = 1;
		room->path = -1;
		file->nb_rooms++;
		(ROOMS)[i++] = room;
	}
	printf("ROOMS: %d\n", file->nb_rooms);
}
