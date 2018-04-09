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

void	add_room_path(t_file *file, t_path *head, char *name)
{
	t_path	*path;
	t_room	*room;
	
	path = (t_path *)malloc(sizeof(t_path));
	path->weight = 0;
	room = find_room(file, name);
//	printf("%p %s\n", room, name);
	path->color = room->color;
//	printf("%sthats my color [%s]%s\n", path->color, name, NORMAL);
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
//	printf("add room done\n");
}

void	get_paths(t_file *file)
{
	char	*name;
	int		path;
	int 	i;
	
	path = -1;
	while (++path < file->nb_paths)
	{
		if (ft_strcmp(file->paths[path], "\0"))
		{
			i = 0;
			while (file->paths[path][i] && file->paths[path][i] != ':')
				i++;
			if (file->paths[path][i++] == '\0')
				break ;
			name = get_name(&(file->paths[path][i]));
			add_room_path(file, NULL, name);
			while (file->paths[path][i])
			{
				while (file->paths[path][i] && file->paths[path][i] != ' ')
					i++;
				if (file->paths[path][i++] == '\0')
					break ;
				name = get_name(&(file->paths[path][i]));
				add_room_path(file, PATHS[file->nb_fpaths], name);
			}
			PATHS[file->nb_fpaths++]->weight = ft_atoi(file->paths[path]);
		}
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
//	printf("COUNT ANTS YAYA\n");
	while (ants > 0)
	{
		i = 0;
//		printf("COUNT ANTS YAYA1\n");
		while (i < file->nb_fpaths && PATHS[i]->weight == -1)
			i++;
		min = i;
//		printf("COUNT ANTS YAYA3\n");
		if (min == file->nb_fpaths)
			break ;
//		printf("%sMIN INDEX: %d%s\n", GREEN, min, NORMAL);
		i = -1;
		while (++i < file->nb_fpaths)
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
	
//	printf("%sASSIGNED ants TO NODE [%d]: %d modulo ants: %d%s\n", YELLOW, 0, PATHS[0]->ants, ants % file->nb_fpaths, NORMAL);
//	printf("first index: %d\n", first_index);
	PATHS[first_index]->ants += ants % file->nb_fpaths;
//	printf("%sASSIGNED ants TO NODE [%d]: %d%s\n", YELLOW, 0, PATHS[0]->ants, NORMAL);
	i = 0;
	while (i < file->nb_fpaths)
		PATHS[i++]->ants += ants / file->nb_fpaths;
}


void	display_ants(t_file *file, int cycle)
{
	int i = 0;
	int paths = 0;
	
	t_path *ptr;
	
	while (paths < file->nb_fpaths)
	{
		ptr = file->final_paths[paths];
		
		while (ptr->next && i++ < cycle - 1)
		{
//			printf("current room %s for path %d and cycle %d: \n", ptr->name, paths, cycle);
			ptr = ptr->next;
		}
//		printf("\n\n");
//		printf("%sANTS: %d%s ", CYAN, ANTS, NORMAL);
		i = 0;
		
		if (ANTS != 0)
		{
//			printf("comin here\n");
//			if (ptr->ants < 1)
//				ptr->nb_ant = -1;
			
			while (i < cycle && ptr)// && ft_strcmp(file->end, ptr->name))
			{
//				printf("%sroom [%s] ants [%d] for path %d%s\n", GREEN, ptr->name, ptr->nb_ant, paths, NORMAL);
//				printf("%sBEFORE FOR PATH [%d] %d ANTS LEFT%s\n", MAGNETA, paths, file->final_paths[paths]->ants, NORMAL);
				if (ft_strcmp(ptr->name, START) && ptr->nb_ant != -1)
					printf("%sL%d-%s %s", ptr->color, ptr->nb_ant, ptr->name, NORMAL);
				if (ft_strcmp(file->end, ptr->name) == 0 && ptr->nb_ant != -1)
					ANTS--;
//				printf("%sAFTER FOR PATH [%d] %d ANTS LEFT%s\n", MAGNETA, paths, file->final_paths[paths]->ants, NORMAL);
				ptr = ptr->prev;
				
				
				//				ptr = ptr->prev;
				i++;
			}
//			file->final_paths[paths]->ants--;
			PATHS[paths]->ants--;
		}
		paths++;
		i = 0;
		
	}
	printf("\n");
	
	
	
	
	int new;
	int next;
	
	paths = 0;
	while (paths < file->nb_fpaths)
	{
		ptr = file->final_paths[paths];
//		printf("%sFOR PATH [%d] %d ANTS LEFT%s\n", MAGNETA, paths, file->final_paths[paths]->ants, NORMAL);
		new = file->final_paths[paths]->ants > 0 ? ptr->nb_ant + 1 : -1;
		if (ANTS != 0)
		{
			while (i < cycle + 1 && ptr)
			{
				next = ptr->nb_ant;
				ptr->nb_ant = new;
//				printf("room [%s] ants [%d] for path %d\n", ptr->name, new, paths);
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
	int 	i;
	t_path* ptr;
	
	i = 0;
//	file->paths = (t_path **)malloc(sizeof(t_room *) * file->nb_paths);
//	ft_bzero(file->rooms, file->nb_paths);
	
	PATHS = (t_path **)malloc(sizeof(t_path *) * file->nb_paths);
//	while (i < file->nb_paths)
//	ft_bzero(PATHS[i], file->nb_paths);
//	printf("paths nb: %d\n", file->nb_paths);
//	file->nb_rooms = 0;
	file->nb_fpaths = 0;
	get_paths(file);
//	printf("get paths done\n");
	count_ants(file);
//	printf("count ants done\n");
//	printf("BEFORE DISPLAY\n");
	while (i < file->nb_fpaths)
	{
		ptr = PATHS[i];
		PATHS[i]->nb_ant = i == 0 ? 1 : PATHS[i - 1]->ants + PATHS[i - 1]->nb_ant;
		while (ptr->next)
			ptr = ptr->next;
		ptr->ants = PATHS[i]->ants;
		i++;
	}
//	printf("AFTER DISPLAY\n");
	
	
	
//	i = 0;
//	while (i < file->nb_fpaths)
//	{
//		printf("ants for room [%d]: %d\n", i, PATHS[i]->ants);
//		i++;
//	}
//	
//	i = 0;
//	while (i < file->nb_fpaths)
//	{
//		printf("nb_ant for path [%d]: %d\n", i, PATHS[i]->nb_ant);
//		i++;
//	}
	
	
	
	display_ants(file, 1);
	
	i = 0;
	t_path *p;
	
//	printf("got them all\n");
//	while (i < file->nb_fpaths)
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
