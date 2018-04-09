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

#include "../includes/lemin.h"

char    *readandstore(void)
{
	char    *buff;
	char    *final;
	
	final = "\0";
	buff = ft_strnew(BUFF_SIZE);
	while (read(0, buff, BUFF_SIZE - 1) > 0)
	{
		final = ft_strjoin(final, buff);
		ft_bzero(buff, BUFF_SIZE);
	}
	free(buff);
	printf("%s%s%s", GREEN, final, NORMAL);
	return (final);
}

int        gnl(t_file *file)
{
	int		size;
	char	*temp;
	
	temp = ft_strnew(BUFF_SIZE);
	LINE = ft_strnew(1);
	//	printf("GNL 1\n");
	while ((file->map[file->offset] == ' ' || file->map[file->offset] == '\n'
			|| file->map[file->offset] == '\t') && file->map[file->offset] != '\0')
		file->offset++;
	//	printf("GNL 2 offset = %d\n", file->offset);
	while (file->map[file->offset] != '\n' && file->map[file->offset] != '\0')
	{
		size = 0;
		
		while (size < BUFF_SIZE && file->map[file->offset] != '\n' &&
			   file->map[file->offset] != '\0')
			//		{
			temp[size++] = file->map[file->offset++];
		//			printf("GNL inside while loop size: %d, offset: %d\n", size, file->offset);
		//		}
		//		printf("[%s]\n", temp);
		LINE = ft_strjoin(LINE, temp);
		//		printf("[%s]\n", LINE);
	}
	//	printf("GNL 3\n");
	if (ft_strcmp(LINE, "\0") == 0)
		//	{
		//		printf("GNL 4\n");
		return (0);
	//	}
	//	printf("GNL 5\n");
	return (1);
}

