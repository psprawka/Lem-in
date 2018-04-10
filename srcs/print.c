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

	first_index = -1;
	ants = file->ants;
	while (ants > 0)
	{
		i = 0;
		while (i < file->nb_fpaths && PATHS[i]->weight == -1)
			i++;
		min = i;
		if (min == file->nb_fpaths)
			break ;
		i = -1;
		while (++i < file->nb_fpaths)
			if (PATHS[i]->weight != -1 && PATHS[min]->weight > PATHS[i]->weight)
				min = i;
		if (PATHS[min]->weight == -1)
			break ;
		PATHS[min]->ants += (ants - PATHS[min]->weight >= 0)
			? PATHS[min]->weight : ants;
		ants -= PATHS[min]->weight;
		PATHS[min]->weight = -1;
		if (first_index == -1)
			first_index = min;
	}
	if (ants <= 0)
		return ;
	PATHS[first_index]->ants += ants % file->nb_fpaths;
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
			ptr = ptr->next;
		i = 0;
		if (ANTS != 0)
		{
			while (i < cycle && ptr)
			{
				if (ft_strcmp(ptr->name, START) && ptr->nb_ant != -1)
					printf("%sL%d-%s %s", ptr->color, ptr->nb_ant, ptr->name, NORMAL);
				if (ft_strcmp(file->end, ptr->name) == 0 && ptr->nb_ant != -1)
					ANTS--;
				ptr = ptr->prev;
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
	while (paths < file->nb_fpaths)
	{
		ptr = file->final_paths[paths];
		new = file->final_paths[paths]->ants > 0 ? ptr->nb_ant + 1 : -1;
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
	if (ANTS > 0)
		display_ants(file, cycle + 1);
}


int 	print_path(t_file *file)
{
	int 	i;
	t_path* ptr;
	
	i = 0;
	PATHS = (t_path **)malloc(sizeof(t_path *) * file->nb_paths);
	file->nb_fpaths = 0;
	get_paths(file);
	count_ants(file);
	while (i < file->nb_fpaths)
	{
		ptr = PATHS[i];
		PATHS[i]->nb_ant = i == 0 ? 1 : PATHS[i - 1]->ants + PATHS[i - 1]->nb_ant;
		while (ptr->next)
			ptr = ptr->next;
		ptr->ants = PATHS[i]->ants;
		i++;
	}
	display_ants(file, 1);
	return 0;
}
