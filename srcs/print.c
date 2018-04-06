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

void	add_room_path(t_file *file, t_room *head, char *name)
{
	t_room *room;
	
	room = (t_room *)malloc(sizeof(t_room));
//	printf("%s\n", name);
	room->weight = 0;
	room->name = name;
	room->next = NULL;
	room->open = 1;
	
	if (head == NULL)
	{
//		printf("seg here1\n");
		file->final_paths[file->nb_rooms] = room;
//		printf("seg here2\n");
	}
	else
	{
//		printf("here %p\n", head);
		while (head->next)
			head = head->next;
//		printf("here2\n");
		head->next = room;
	}
//	prev->next = room;
	
}

void	get_paths(t_file *file)
{
	char	*name;
	int		path;
	int 	i;
	
	path = 0;
//	printf("get paths\n");
	while (path < file->nb_paths)
	{
		if (ft_strcmp(file->paths[path], "\0"))
		{
//			printf("got path [%s]\n", file->paths[path]);
//			create_path(file, file->paths[path]);
			i = 0;
			while (file->paths[path][i] && file->paths[path][i] != ':')
				i++;
			if (file->paths[path][i] == '\0')
				break ;
			i++;
			name = get_name(&(file->paths[path][i]));
			add_room_path(file, NULL, name);
			while (file->paths[path][i])
			{
				while (file->paths[path][i] && file->paths[path][i] != ' ')
					i++;
				if (file->paths[path][i] == '\0')
					break ;
				i++;
				name = get_name(&(file->paths[path][i]));
//				printf("HERE3 %d\n", file->nb_rooms);
				add_room_path(file, file->final_paths[file->nb_rooms], name);
				
			}
//			printf("after path found\n");
			file->final_paths[file->nb_rooms++]->weight = ft_atoi(file->paths[path]);
//			printf("got path\n");
		}
		path++;
		
	}
	
}

#include <strings.h>
int 	print_path(t_file *file)
{
	int i = 0;
	
//	file->rooms = (t_room **)malloc(sizeof(t_room *) * file->nb_paths);
//	ft_bzero(file->rooms, file->nb_paths);
	
	file->final_paths = (t_room **)malloc(sizeof(t_room *) * file->nb_paths);
//	while (i < file->nb_paths)
//	ft_bzero(file->final_paths[i], file->nb_paths);
//	printf("paths nb: %d\n", file->nb_paths);
	file->nb_rooms = 0;
	
	get_paths(file);
	
	i = 0;
	t_room *p;
	
//	printf("got them all\n");
	while (i < file->nb_rooms)
	{
		printf("path %d: ", i);
		p = file->final_paths[i];
		while (p != NULL)
		{
			printf("%s -> ", p->name);
			p = p->next;
		}
		printf("null\n");
		i++;
	}
	return 0;
}
