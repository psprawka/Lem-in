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

#include "lemin.h"

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
		error(1);
	file->ants = ft_atoi(LINE);
	file->ants2 = file->ants;
	while (LINE[i] < 58 && LINE[i] > 47)
		i++;
	while (LINE[i] == '\t' || LINE[i] == ' ')
		i++;
	if (LINE[i] != '\0')
		error(1);
}

char	*command(t_file *file, int i)
{
	if (ft_strncmp(&(LINE[i]), "##end\0", 6) == 0 && gnl(file))
	{
		if (END != NULL)
			error(10);
		END = get_name(LINE);
		return ("END");
	}
	else if (ft_strncmp(&(LINE[i]), "##start\0", 8) == 0 && gnl(file))
	{
		if (START != NULL)
			error(10);
		START = get_name(LINE);
		return ("START");
	}
	return (NULL);
}

char	*comment_command(t_file *file)
{
	int		i;
	char	*color;

	i = 0;
	if (LINE[i] != '#')
		return (NULL);
	while (LINE[i] != '#' && LINE[i] != '\0')
		i++;
	if (LINE[i] == '\0')
		return (NULL);
	if (LINE[i + 1] != '#')
		LINE[i] = '\0';
	else
	{
		if (command(file, i) != NULL)
			return (NULL);
		else if ((color = colorsfind(file, &(LINE[i]))) != NULL)
			return (color);
	}
	gnl(file);
	comment_command(file);
	return (NULL);
}

void	parse(t_file *file)
{
	if (gnl(file) == 0)
		error(4);
	comment_command(file);
	get_ants(file);
	rooms(file, 0);
	if (file->ants < 0 || file->ants > 65000)
		error(1);
	if (START == NULL || END == NULL)
		error(2);
	connect(file);
}
