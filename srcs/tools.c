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

t_room	*find_room(t_file *file, char *to_find)
{
	t_room	*ptr;
	int		i;

	i = 0;
	while (i < file->nb_rooms)
	{
		ptr = ROOMS[i];
		if (ft_strcmp(ptr->name, to_find) == 0)
			return (ptr);
		i++;
	}
	return ((t_room *)NULL);
}

int		room_pos(t_file *file, char *to_find)
{
	t_room	*ptr;
	int		i;

	i = 0;
	while (i < file->nb_rooms)
	{
		ptr = ROOMS[i];
		if (ft_strcmp(ptr->name, to_find) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	rooms_exist(t_file *file, char *r1, char *r2)
{
	int	i;
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

void	add_room_path(t_file *file, t_path *head, char *name)
{
	t_path	*path;
	t_room	*room;
	
	path = (t_path *)malloc(sizeof(t_path));
	path->weight = 0;
	room = find_room(file, name);
	path->color = room->color;
	path->name = ft_strdup(name);
	path->next = NULL;
	if (head == NULL)
	{
		PATHS[file->nb_fpaths] = path;
		path->prev = NULL;
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = path;
		path->prev = head;
	}
	free(name);
}
