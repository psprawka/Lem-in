/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 20:33:10 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/01 20:33:11 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#define MAP		file->map
#define OFFSET	file->offset

char	*readandstore(void)
{
	char	*buff;
	char	*final;

	final = ft_strnew(1);
	buff = ft_strnew(BUFF_SIZE);
	while (read(0, buff, BUFF_SIZE - 1) > 0)
	{
		final = ft_strjoin(final, buff);
		ft_bzero(buff, BUFF_SIZE);
	}
	free(buff);
	ft_printf("%s%s%s", ORANGE, final, NORMAL);
	return (final);
}

int		gnl(t_file *file)
{
	int		size;
	char	*temp;

	temp = ft_strnew(BUFF_SIZE);
	if (LINE)
		free(LINE);
	LINE = ft_strnew(1);
	while (MAP[OFFSET] != '\n' && MAP[OFFSET] != '\0')
	{
		size = 0;
		while (size < BUFF_SIZE && MAP[OFFSET] != '\n' && MAP[OFFSET] != '\0')
			temp[size++] = MAP[OFFSET++];
		LINE = ft_strjoin(LINE, temp);
		free(temp);
	}
	if (MAP[OFFSET] == '\n')
		OFFSET++;
	if (ft_strcmp(LINE, "\0") == 0 && MAP[OFFSET] != '\0')
		error(12);
	if (ft_strcmp(LINE, "\0") == 0)
	{
		free(temp);
		return (0);
	}
	return (1);
}
