/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:26:01 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/01 19:26:03 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		if_connect(t_file *file, int i)
{
	while (LINE[i] == ' ' || LINE[i] == '\t')
		i++;
	while (LINE[i] && LINE[i] != '-' )
		i++;
	if (LINE[i++] != '-')
		error();
	while (LINE[i] && (LINE[i] != ' ' && LINE[i] != '\t'))
		i++;
	return (LINE[i] == '\0' ? 1 : 0);
}

int		check_row(t_file *file, int i, char *to_compare, int w)
{
	t_room *ptr;

	ptr = ROOMS[i];
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->name, to_compare) == 0 || w > 1)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	add_room(int weight, char *name, t_room *prev)
{
	t_room *room;

	room = (t_room *)malloc(sizeof(t_room));
	room->weight = weight;
	room->name = name;
	room->next = NULL;
	room->open = 1;
	if (prev->next != NULL)
		room->next = prev->next;
	prev->next = room;
}

void	make_connect(t_file *file, char *r1, char *r2)
{
	t_room	*ptr;
	int		i;
	
	i = -1;
	while (i++ < file->nb_rooms)
	{
		ptr = ROOMS[i];
		while (ptr != NULL)
		{
			if (ft_strcmp(ptr->name, r1) == 0 && check_row(file, i, r2, ptr->weight + 1) == 0)
				add_room(ptr->weight + 1, r2, ptr);
			ptr = ptr->next;
		}
	}
	i = -1;
	while (i++ < file->nb_rooms)
	{
		ptr = ROOMS[i];
		while (ptr != NULL)
		{
			if (ft_strcmp(ptr->name, r2) == 0 && check_row(file, i, r1, ptr->weight + 1) == 0)
				add_room(ptr->weight + 1, r1, ptr);
			ptr = ptr->next;
		}
	}
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
		error();
}

void	connect(t_file *file)
{
	char	*room1;
	char	*room2;
	int		i;
	
	while (ft_strcmp(LINE, "\0") != 0)
	{
		i = 0;
		comment_command(file);
		if (if_connect(file, 0) == 0)
			error();
		room1 = ft_strncpy(LINE, ft_strlen_chr(LINE, '-'));
		while (LINE[i] != '-')
			i++;
		i++;
		room2 = get_name(&(LINE[i]));
		rooms_exist(file, room1, room2);
		make_connect(file, room1, room2);
		if (gnl(file) == 0)
			break;
	}
}

