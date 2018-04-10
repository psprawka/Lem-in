/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 22:06:41 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/02 22:06:44 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	free_rooms(t_file *file)
{
	int		i;
	t_room	*ptr;
	t_room	*prev;

	i = 0;
	while (i < file->nb_rooms)
	{
		prev = file->rooms[i++];
		ptr = prev->next;
		while (prev != NULL)
		{
			free(prev->name);
			free(prev);
			prev = ptr;
			if (prev)
				ptr = prev->next;
		}
	}
}

void	free_paths(t_file *file)
{
	int i;

	i = 0;
	while (i < file->nb_paths)
		free(file->paths[i++]);
	free(file->paths);
}

void	free_file(t_file *file)
{
	free(file->end);
	free(file->start);
	free(file->line);
	free(file->map);
	free_rooms(file);
	free_paths(file);
}
