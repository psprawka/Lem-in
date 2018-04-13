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

#include "lemin.h"

#define IS_DIGIT(c)	(c > 47 && c < 58) ? 1 : 0

int		if_room(char *line, int i)
{
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i++;
	if (line[i] == '-')
		i++;
	while (IS_DIGIT(line[i]))
		i++;
	i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] == '-')
		i++;
	while (IS_DIGIT(line[i]))
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

void	rooms(t_file *file, int i)
{
	t_room	*room;
	char	*color;

	while (gnl(file) != 0 && (room = (t_room *)malloc(sizeof(t_room))))
	{
		color = comment_command(file);
		if (if_room(LINE, 0) == 0)
		{
			if (if_connect(file, 0))
			{
				free(room);
				break ;
			}
			error(7);
		}
		room->name = get_name(LINE);
		room->weight = 0;
		room->next = NULL;
		room->color = color == NULL ? NORMAL : color;
		room->open = 1;
		room->path = -1;
		(ROOMS)[file->nb_rooms++] = room;
	}
	file->nb_rooms == 0 ? error(11) : write(1, "", 0);
	ROOMS[file->nb_rooms] = NULL;
}
