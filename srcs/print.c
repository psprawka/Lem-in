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

# define PATHS 		file->final_paths
# define ANTS 		file->ants
# define NB_PATHS 	file->nb_rooms

void	add_room_path(t_file *file, t_path *head, char *name)
{
	t_path *path;
	
	path = (t_path *)malloc(sizeof(t_path));
//	printf("%s\n", name);
	path->weight = 0;
	path->name = name;
	path->next = NULL;
	
	if (head == NULL)
	{
//		printf("seg here1\n");
		PATHS[file->nb_rooms] = path;
		path->prev = NULL;
//		printf("seg here2\n");
	}
	else
	{
//		printf("here %p\n", head);
		while (head->next)
			head = head->next;
//		printf("here2\n");
		head->next = path;
		path->prev = head;
	}
//	prev->next = path;
	
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
				add_room_path(file, PATHS[file->nb_rooms], name);
				
			}
//			printf("after path found\n");
			PATHS[file->nb_rooms++]->weight = ft_atoi(file->paths[path]);
//			printf("got path\n");
		}
		path++;
		
	}
	
}



void		count_ants(t_file *file)
{
	int		min;
	int		first_index;
	int		i;
	int		ants;
	
//	min = 0;
	first_index = -1;
	ants = file->ants;
	while (ants > 0)
	{
		i = 0;
		while (i < NB_PATHS && PATHS[i]->weight == -1)
			i++;
		min = i;
		if (min == NB_PATHS)
			break ;
//		printf("%sMIN INDEX: %d%s\n", GREEN, min, NORMAL);
		i = -1;
		while (++i < NB_PATHS)
//		{
			if (PATHS[i]->weight != -1 && PATHS[min]->weight > PATHS[i]->weight)
				min = i;
//			i++;
//		}
//		printf("%sCURRENT WEIGHT[%d]: %d%s\n", CYAN, min, PATHS[min]->weight, NORMAL);
		if (PATHS[min]->weight == -1)
			break ;
		
		PATHS[min]->ants += (ants - PATHS[min]->weight >= 0)
			? PATHS[min]->weight : ants;
//		printf("%sASSIGNED ants[%d]: %d%s\n", YELLOW, min, PATHS[min]->weight, NORMAL);

		ants -= PATHS[min]->weight;
		PATHS[min]->weight = -1;
		
		if (first_index == -1)
			first_index = min;
		
	}
	if (ants <= 0)
		return ;
	
//	printf("%sASSIGNED ants TO NODE [%d]: %d modulo ants: %d%s\n", YELLOW, 0, PATHS[0]->ants, ants % NB_PATHS, NORMAL);
//	printf("first index: %d\n", first_index);
	PATHS[first_index]->ants += ants % NB_PATHS;
//	printf("%sASSIGNED ants TO NODE [%d]: %d%s\n", YELLOW, 0, PATHS[0]->ants, NORMAL);
	i = 0;
	while (i < NB_PATHS)
		PATHS[i++]->ants += ants / NB_PATHS;
}


void	display_ants(t_file *file, int cycle)
{
	int i = 0;
	int paths = 0;
	
	t_path *ptr;
	
	while (paths < NB_PATHS)
	{
		ptr = file->final_paths[paths];
		
//		while (ptr->next && i < cycle - 1)
//			ptr = ptr->next;
//		printf("current room for path %d and cycle %d: %s\n", paths, cycle, ptr->name);
		
//		i = 0;
		if (ANTS != 0)
		{
			if (ptr->ants < 1)
				ptr->nb_ant = -1;
				
			while (i < cycle && ptr)// && ft_strcmp(file->end, ptr->name))
			{
				if (i != 0 && ptr->nb_ant < file->ants2 + 1 && ptr->nb_ant != -1)
					printf("L%d-%s ", ptr->nb_ant, ptr->name);
				if (ft_strcmp(file->end, ptr->name) == 0)
					ANTS--;
				ptr = ptr->next;
				//				ptr = ptr->prev;
				i++;
			}
			
			PATHS[paths]->ants--;
		}
		paths++;
		i = 0;
		
	}
	printf("\n");
	
	
	
	
	int new;
	int next;
	
	paths = 0;
	while (paths < NB_PATHS)
	{
		ptr = file->final_paths[paths];
		new = ptr->nb_ant == -1 ? -1 : ptr->nb_ant + 1;
		if (ANTS != 0)
		{
			while (i < cycle + 1 && ptr)
			{
				next = ptr->nb_ant;
				ptr->nb_ant = new;
				new = next;
				ptr = ptr->next;
				i++;
			}
		}
		paths++;
		i = 0;
	}
//	printf("CYCLE %d ants: %d done!\n", cycle, ANTS);
	if (ANTS > 0)
		display_ants(file, cycle + 1);
//	printf("path done\n");
}


int 	print_path(t_file *file)
{
	int i = 0;
	
//	file->paths = (t_path **)malloc(sizeof(t_room *) * file->nb_paths);
//	ft_bzero(file->rooms, file->nb_paths);
	
	PATHS = (t_path **)malloc(sizeof(t_path *) * file->nb_paths);
//	while (i < file->nb_paths)
//	ft_bzero(PATHS[i], file->nb_paths);
//	printf("paths nb: %d\n", file->nb_paths);
	file->nb_rooms = 0;
	
	get_paths(file);
	count_ants(file);
//	printf("BEFORE DISPLAY\n");
	while (i < file->nb_rooms)
	{
		PATHS[i]->nb_ant = i == 0 ? 1 : PATHS[i - 1]->ants + PATHS[i - 1]->nb_ant;
		i++;
	}
//	printf("AFTER DISPLAY\n");
	
	
	
//	i = 0;
//	while (i < file->nb_rooms)
//	{
//		printf("ants for room [%d]: %d\n", i, PATHS[i]->ants);
//		i++;
//	}
//	
//	i = 0;
//	while (i < file->nb_rooms)
//	{
//		printf("nb_ant for path [%d]: %d\n", i, PATHS[i]->nb_ant);
//		i++;
//	}
	
	
	
	display_ants(file, 1);
	
	i = 0;
	t_path *p;
	
//	printf("got them all\n");
//	while (i < file->nb_rooms)
//	{
//		printf("path %d: ", i);
//		p = PATHS[i];
//		while (p->next != NULL)
//		{
//			printf("%s -> ", p->name);
//			p = p->next;
//		}
//		printf("%s -> null\n", p->name);
//
//		while (p->prev != NULL)
//		{
//			printf("%s -> ", p->name);
//			p = p->prev;
//		}
//		printf("%s -> null\n", p->name);
//		i++;
//	}
//
	
	return 0;
}
