/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:25:23 by psprawka          #+#    #+#             */
/*   Updated: 2018/03/27 12:25:26 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

char	*get_name(char *line)
{
	int		i;
	int		iname;
	char	*str;

	i = 0;
	iname = 0;
	str = ft_strnew(MAX_NAME_LEN);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		str[iname++] = line[i++];
	return (str);
}

void	get_ants(t_file *file)
{
	int	i;
	
	i = 0;
	if (LINE[i] > 57 || LINE[i] < 48)
		error();
	file->ants = ft_atoi(LINE);
	file->ants2 = file->ants;
	while (LINE[i] < 58 && LINE[i] > 47)
		i++;
	while (LINE[i] == '\t' || LINE[i] == ' ')
		i++;
	if (LINE[i] != '\0')
		error();
}

void   comment_command(t_file *file)
{
	int i;
	
	i = 0;
	while (LINE[i] != '#' && LINE[i] != '\0')
		i++;
	if (LINE[i] == '\0')
		return ;
	if (LINE[i + 1] != '#')
		LINE[i] = '\0';
	else
	{
		if (END == NULL && ft_strncmp(&(LINE[i]), "##end", 5) == 0 && gnl(file))
			END = get_name(LINE);
		else if (START == NULL && ft_strncmp(&(LINE[i]), "##start", 7) == 0
				 && gnl(file))
			START = get_name(LINE);
		else
			error();
	}
	if (ft_strcmp(LINE, "\0") == 0)
	{
		gnl(file);
		comment_command(file);
	}
}

void    parse(t_file *file)
{
	if (gnl(file) == 0)
		error();
	
	get_ants(file);
	rooms(file);
	if (file->ants < 0 || START == NULL || END == NULL)
		error();
	connect(file);
}
