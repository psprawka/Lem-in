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
		error(1);
	file->ants = ft_atoi(LINE);
	file->ants2 = file->ants;
	while (LINE[i] < 58 && LINE[i] > 47)
		i++;
	while (LINE[i] == '\t' || LINE[i] == ' ')
		i++;
	if (LINE[i] != '\0')
		error(7);
}


char	*colorsfind(t_file *file, char *command)
{
	printf("command [%s]\n", command);
	if (ft_strncmp(command, "##green", 7) == 0 && gnl(file))
		return (GREEN);
	if (ft_strncmp(command, "##red", 5) == 0 && gnl(file))
		return (RED);
	if (ft_strncmp(command, "##yellow", 8) == 0 && gnl(file))
		return (YELLOW);
	if (ft_strncmp(command, "##cyan", 6) == 0 && gnl(file))
		return (CYAN);
	if (ft_strncmp(command, "##blue", 6) == 0 && gnl(file))
		return (BLUE);
	if (ft_strncmp(command, "##magneta", 9) == 0 && gnl(file))
		return (GREEN);
//	printf("lololol error you bitch\n");
	error(3);
	return (NULL);
}


char	*comment_command(t_file *file)
{
	int		i;
	char	*color;
	
	i = 0;
	while (LINE[i] != '#' && LINE[i] != '\0')
		i++;
	if (LINE[i] == '\0')
		return (NULL);
	if (LINE[i + 1] != '#')
		LINE[i] = '\0';
	else
	{
		if (END == NULL && ft_strncmp(&(LINE[i]), "##end", 5) == 0 && gnl(file))
			END = get_name(LINE);
		else if (START == NULL && ft_strncmp(&(LINE[i]), "##start", 7) == 0
				 && gnl(file))
			START = get_name(LINE);
		else if ((color = colorsfind(file, &(LINE[i]))) != NULL)
			return (color);
	}
	if (ft_strcmp(LINE, "\0") == 0)
	{
		gnl(file);
		comment_command(file);
	}
	return (NULL);
}

void    parse(t_file *file)
{
	if (gnl(file) == 0)
		error(4);
	
	get_ants(file);
	rooms(file);
	if (file->ants < 0)
		error(1);
	if (START == NULL || END == NULL)
		error(2);
	connect(file);
}
