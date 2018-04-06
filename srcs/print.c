/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:32:42 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/04 19:32:43 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	add_room(t_room *head)
{
	t_room *room;
	
	head = file->rooms[file->nb_rooms];
	room = (t_room *)malloc(sizeof(t_room));
	
	room->weight = weight;
	room->name = name;
	room->next = NULL;
	room->open = 1;
	
	if (head == NULL)
		file->rooms[file->nb_rooms++] = room;
	else
	{
		while (head->next)
			head = head->next;
		
	}
//	prev->next = room;
	
}


void	create_path(t_file *file, char *str)
{
	t_room	*first;
	char	*name
	
	while (str[i])
	{
		while (str[i] && str[i] != ':' && str[i] != ' ')
			i++;
		i++;
		name = get_name(&(str[i]));
		add_room()
	}
	first->weight = ft_atoi(str);
}


void	get_paths(t_file *file)
{
	int path;
	
	path = 0;
	while (path < file->nb_paths)
	{
		if (ft_strcmp(file->paths[path], "\0"))
		{
			str = file->paths[path];
			create_path(file, str);
		}
		path++;
	}
}

int 	print_path(t_file *file)
{
	free_rooms(file);
	
	file->rooms = (t_room **)malloc(sizeof(t_room *) * file->nb_paths);
	ft_bzero(file->rooms, file->nb_paths);
	file->nb_rooms = 0;
	
	get_paths(file);
	return 0;
}
