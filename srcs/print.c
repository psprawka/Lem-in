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

#define COLOR	ptr->color
#define ANT		ptr->nb_ant

void	get_paths(t_file *file, int path, int i)
{
	char	*name;

	while (++path < file->nb_paths && (i = 0) != 1)
	{
		if (ft_strcmp(ALL_PATHS[path], "\0"))
		{
			while (ALL_PATHS[path][i] && ALL_PATHS[path][i] != ':')
				i++;
			if (ALL_PATHS[path][i++] == '\0')
				break ;
			name = get_name(&(ALL_PATHS[path][i]));
			add_room_path(file, NULL, name);
			while (ALL_PATHS[path][i])
			{
				while (ALL_PATHS[path][i] && ALL_PATHS[path][i] != ' ')
					i++;
				if (ALL_PATHS[path][i++] == '\0')
					break ;
				name = get_name(&(ALL_PATHS[path][i]));
				add_room_path(file, PATHS[file->nb_fpaths], name);
			}
			PATHS[file->nb_fpaths++]->weight = ft_atoi(ALL_PATHS[path]);
		}
	}
}

#define MIN_W	PATHS[min]->weight

void	count_ants(t_file *file, int first_index, int ants, int i)
{
	int	min;

	while (ants > 0 && (i = 0) != 1)
	{
		while (i < file->nb_fpaths && PATHS[i]->weight == -1)
			i++;
		min = i;
		if ((i = -1) && min == file->nb_fpaths)
			break ;
		while (++i < file->nb_fpaths)
			if (PATHS[i]->weight != -1 && MIN_W > PATHS[i]->weight)
				min = i;
		if (MIN_W == -1)
			break ;
		PATHS[min]->ants += (ants - MIN_W >= 0) ? MIN_W : ants;
		ants -= MIN_W;
		MIN_W = -1;
		first_index = first_index == -1 ? min : first_index;
	}
	if (ants <= 0)
		return ;
	PATHS[first_index]->ants += ants % file->nb_fpaths;
	i = 0;
	while (i < file->nb_fpaths)
		PATHS[i++]->ants += ants / file->nb_fpaths;
}

void	move_ants(t_file *file, int cycle, int i, int paths)
{
	int		new;
	int		next;
	t_path	*ptr;

	while (paths < file->nb_fpaths)
	{
		i = -1;
		ptr = file->final_paths[paths];
		new = file->final_paths[paths]->ants > 0 ? ANT + 1 : -1;
		if (ANTS != 0)
		{
			while (++i < cycle + 1 && ptr)
			{
				next = ANT;
				ANT = new;
				new = next;
				ptr = ptr->next;
			}
		}
		paths++;
	}
	if (ANTS > 0)
		display_ants(file, cycle + 1, -1);
}

void	display_ants(t_file *file, int cycle, int paths)
{
	int		i;
	t_path	*ptr;

	while (++paths < file->nb_fpaths)
	{
		i = 0;
		ptr = file->final_paths[paths];
		while (ptr->next && i++ < cycle - 1)
			ptr = ptr->next;
		i = -1;
		if (ANTS != 0)
		{
			while (++i < cycle && ptr)
			{
				if (ft_strcmp(ptr->name, START) && ANT != -1)
					printf("%sL%d-%s %s", COLOR, ANT, ptr->name, NORMAL);
				if (ft_strcmp(file->end, ptr->name) == 0 && ANT != -1)
					ANTS--;
				ptr = ptr->prev;
			}
			PATHS[paths]->ants--;
		}
	}
	printf("\n");
	move_ants(file, cycle, 0, 0);
}

int		print_path(t_file *file)
{
	int		i;
	t_path	*ptr;

	i = 0;
	PATHS = (t_path **)malloc(sizeof(t_path *) * file->nb_paths);
	file->nb_fpaths = 0;
	get_paths(file, -1, 0);
	count_ants(file, -1, file->ants, 0);
	while (i < file->nb_fpaths)
	{
		ptr = PATHS[i];
		PATHS[i]->nb_ant = i == 0 ? 1 :
			PATHS[i - 1]->ants + PATHS[i - 1]->nb_ant;
		while (ptr->next)
			ptr = ptr->next;
		ptr->ants = PATHS[i]->ants;
		i++;
	}
	display_ants(file, 1, -1);
	return (0);
}
