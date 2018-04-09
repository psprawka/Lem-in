/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 11:09:14 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/02 11:09:16 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room	*find_room(t_file *file, char *to_find)
{
	t_room *ptr;
	int i;
	
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
	t_room *ptr;
	int i;
	
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

int		ftt_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] < s2[i]) || (s1[i] > s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int		multi_path(t_file *file, t_room *ptr)
{
	int		curr;
	int		weight;
	char	*name;
	
	curr = 0;
	name = ft_strnew(1);
	name = ft_strjoin(name, " ");
	name = ft_strjoin(name, ptr->name);
	name = ft_strjoin(name, " ");
	
	while (curr < file->nb_paths)
	{
		if (ft_strcmp(file->paths[curr], "\0") != 0 &&
			ft_strstr(file->paths[curr], name) == 1)
		{
			weight = ft_atoi(file->paths[curr]);
			if (find_room(file, file->end)->weight >= weight)
				return (-1);
			else
			{
				free(file->paths[curr]);
				file->paths[curr] = ft_strnew(1);
			}
		}
		curr++;
	}
	return (0);
}



void	save_path(t_file *file)
{
	t_room	*ptr;
    char	*path;
	char	*weight;
	
	path = ft_strnew(1);
	ptr = find_room(file, file->start);
	weight = ft_itoa(find_room(file, file->end)->weight);
	path = ft_strjoin(path, weight);
	free(weight);
	path = ft_strjoin(path, ":");
	while (ptr && ft_strcmp(ptr->name, file->end) != 0)
	{
		if (multi_path(file, ptr) == -1)
			return ;
		path = ft_strjoin(path, ptr->name);
		path = ft_strjoin(path, " ");
		ptr = find_room(file, (ROOMS[ptr->path])->name);
	}
	path = ft_strjoin(path, ptr->name);
	file->paths[file->nb_paths++] = path;
}

int        find_path(t_file *file, t_room *ptr, int w)
{
    t_room *head;
	
    head = ptr;
	if (head)
	{
		head->open = false;
		head->weight = w;
	}
    while (ptr)
    {
		while (ptr && find_room(file, ptr->name)->open == false)
			ptr = ptr->next;
		if (ptr && ft_strcmp(ptr->name, file->end) == 0)
		{
			head->path = room_pos(file, ptr->name);
			find_room(file, file->end)->weight = w + 1;
			save_path(file);
			ptr = ptr->next;
		}
		else if (ptr)
		{
			head->path = room_pos(file, ptr->name);
			find_path(file, ROOMS[room_pos(file, ptr->name)], 1 + w);
			ptr = ptr->next;
		}
	}
	if (head)
		head->open = true;
    return (1);
}

void	solve(t_file *file)
{
	t_room	*curr;

	
	printf("START %s | CURRENT %s\n", file->start, "curr->name");
	if ((curr = find_room(file, file->start)) == NULL)
		error();
	printf("\n------------------------------------------------------------\n\n");
	if (find_path(file, curr, 0) == 0)
		error();
	
	
	int i = 0;
	
	while (i < file->nb_paths)
	{
		printf("PATH[%d]: [%s]\n", i, file->paths[i]);
		i++;
	}
	
	print_path(file);
	
}
