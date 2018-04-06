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
	while (file->line[i] == ' ' || file->line[i] == '\t')
		i++;
	while (file->line[i] && file->line[i] != '-' )
		i++;
	if (file->line[i++] != '-')
		error();
	
	while (file->line[i] && (file->line[i] != ' ' && file->line[i] != '\t'))
		i++;
	return (file->line[i] == '\0' ? 1 : 0);
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
	//	printf("%sADDING A ROOM! curr_name: %s | name_to_add: %s%s\n", MAGNETA, prev->name, name, NORMAL);

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
	int		i = 0;
	t_room	*ptr;
//	printf("MAKE CONNECT! r1: [%s] r2: [%s]\n", r1, r2);
	while (i < file->nb_rooms)
	{
//		printf("FIRST WHILE LOOP: %d\n", i);
		ptr = ROOMS[i];
		while (ptr != NULL)
		{
			if (ft_strcmp(ptr->name, r1) == 0 && check_row(file, i, r2, ptr->weight + 1) == 0)
				add_room(ptr->weight + 1, r2, ptr);
			ptr = ptr->next;
		}
		i++;
	}
	
	i = 0;
	while (i < file->nb_rooms)
	{
//		printf("SECOND WHILE LOOP: %d\n", i);
		ptr = ROOMS[i];
		while (ptr != NULL)
		{
			if (ft_strcmp(ptr->name, r2) == 0 && check_row(file, i, r1, ptr->weight + 1) == 0)
				add_room(ptr->weight + 1, r1, ptr);
			ptr = ptr->next;
		}
		i++;
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
	
	
	while (ft_strcmp(file->line, "\0") != 0)
	{
		i = 0;
//		printf("%sCONNECT [%s]%s\n", YELLOW, file->line, NORMAL);
		comment_command(file);
//		printf("AFTER COMMAND\n");
		if (if_connect(file, 0) == 0)
			error();
		room1 = ft_strncpy(file->line, ft_strlen_chr(file->line, '-'));
//		printf("AFTER ROOM1\n");
		while (file->line[i] != '-')
			i++;
		i++;
		room2 = get_name(&(file->line[i]));
//		printf("AFTER ROOM2\n");
		rooms_exist(file, room1, room2);
			
		make_connect(file, room1, room2);
		
		if (gnl(file) == 0)
			break;
	}
}

