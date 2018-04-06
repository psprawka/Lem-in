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
//	printf("YOOOOOOO\n");
	i = 0;
	while (i < file->nb_rooms)
	{
//		printf("LOL\n");
		ptr = ROOMS[i];
		if (ft_strcmp(ptr->name, to_find) == 0)
		{
//			printf("BYE BYE\n");
			return (ptr);
		}
		i++;
//		if (i > 99) printf("YOOOOOOO i = %d nb_rooms = %d\n", i, file->nb_rooms);
	}
//	printf("YOOOOOOO2\n");
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
//		printf("strcmp\ns1: [%s]\ns2: [%s]\n", s1, s2);
//		printf(" [%s] [%s] ", s1, s2);
	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] < s2[i]) || (s1[i] > s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

//void	save_path(t_file *file)
//{
//	t_room	*ptr;
//    char	*path;
//	char	*weight;
//	int		i;
//
//	path = ft_strnew(1);
//	ptr = find_room(file, file->start);
//	i = 0;
//	while (ptr && ft_strcmp(ptr->name, file->end) != 0) //&& ptr->path >= 0
//	{
//		path = ft_strjoin(path, ptr->name);
//		path = ft_strjoin(path, " ");
//		ptr = find_room(file, (ROOMS[ptr->path])->name);
//		i++;
//	}
//	path = ft_strjoin(path, ptr->name);
//	path = ft_strjoin(path, ":");
//	weight = ft_itoa(i);
//	path = ft_strjoin(path, weight);
//	free(weight);
//    printf("%spath: [%s]%s\n\n", MAGNETA, path, NORMAL);
//	file->paths[file->nb_paths++] = path;
//}


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
//		printf("%sCHECKIN PATH \n", GREEN, file->paths[curr], NORMAL);
		if (ft_strcmp(file->paths[curr], "\0") != 0 && ft_strstr(file->paths[curr], name) == 1)
		{
			weight = ft_atoi(file->paths[curr]); //waga sciezki
			if (find_room(file, file->end)->weight >= weight) //waga noda >= wadze sciezki
				return (-1);
			else
			{
//				printf("%d curr\n", curr);
//				printf("%sChanging... %s%s\n", GREEN, file->paths[curr], NORMAL);
				free(file->paths[curr]);
				file->paths[curr] = ft_strnew(1);
//				printf("%sAfter... [%s]%s\n", NORMAL, file->paths[curr], NORMAL);
			}
		}
//		printf("CURR %d\n", curr);
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
//	printf("GOOD TO CHANGE!\n");
//	printf("%sAfter... [%s]%s\n", YELLOW, file->paths[0], NORMAL);
//    printf("%d %spath: [%s]%s\n\n", find_room(file, file->end)->weight, MAGNETA, path, NORMAL);
	
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
	
//	printf("%sNEW PROCESS FOR [%s]%s\n", YELLOW, ptr->name, NORMAL);
    while (ptr)
    {
//		printf("INSIDE WHILE with pointer [%s] \n", ptr->name);
//		find_room(file, ptr->name)->open = false;
//		printf("HERE\n");
		while (ptr && find_room(file, ptr->name)->open == false)
		{
//			printf("for process [%s] room closed: %s\n", head->name, ptr->name);
			ptr = ptr->next;
		}
//		printf("HERE\n");
//		find_room(file, file->end)->open = true;
		
		if (ptr && ft_strcmp(ptr->name, file->end) == 0)
		{
//			printf("%sEND FOUND[%s]%s\n", YELLOW, ptr->name, NORMAL);
			
			head->path = room_pos(file, ptr->name);
			find_room(file, file->end)->weight = w + 1;
			save_path(file);
			ptr = ptr->next;
//			find_room(file, file->end)->open = true;
		}
		else if (ptr)
		{
			head->path = room_pos(file, ptr->name);
//			printf("FOR HEAD: %s path saved: %s\n", head->name, ptr->name);
			find_path(file, ROOMS[room_pos(file, ptr->name)], 1 + w);
//			find_room(file, ptr->name)->open = true;
//			ptr = ptr->next;
			ptr = ptr->next;
//			if (ptr) printf("opening [%s]\n", find_room(file, ptr->name)->name);
		}
		
	}
	
	if (head)
	{
//		printf("%sEND OF %s PROCESS%s\n", CYAN, head->name, NORMAL);
		head->open = true;
	}
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
