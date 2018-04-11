/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:24:59 by psprawka          #+#    #+#             */
/*   Updated: 2018/03/27 12:25:01 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 		100
# define MAX_NAME_LEN 	1000
# define MAX_PATHS_NB	100000
# define MAX_ROOMS_NB	100000

# define ROOMS			file->rooms
# define START			file->start
# define END			file->end
# define LINE			file->line
# define PATHS 			file->final_paths
# define ALL_PATHS 		file->paths
# define ANTS 			file->ants

# define NORMAL			"\x1B[0m"
# define RED			"\x1B[31m"
# define GREEN			"\x1B[32m"
# define YELLOW			"\x1B[33m"
# define BLUE			"\x1B[34m"
# define MAGNETA		"\x1B[35m"
# define CYAN			"\x1B[36m"
# define PINK			"\033[38;5;200m"
# define ORANGE			"\033[38;5;208m"
# define PURPLE			"\033[38;5;55m"
# define MAROON			"\033[38;5;88m"
# define GREY			"\033[38;5;246m"

typedef struct	s_room
{
	struct s_room	*next;
	char			*name;
	char			*color;
	int				weight;
	int				path;
	int				open;
}				t_room;

typedef struct	s_path
{
	struct s_path	*next;
	struct s_path	*prev;
	char			*name;
	char			*color;
	int				weight;
	int				ants;
	int				nb_ant;
}				t_path;

typedef struct	s_file
{
	int				ants;
	int				ants2;
	int				nb_paths;
	int				nb_fpaths;
	char			**paths;
	char			*map;
	char			*line;
	struct s_room	**rooms;
	struct s_path	**final_paths;
	int				nb_rooms;
	char			*start;
	char			*end;
	int				offset;
}				t_file;

/*
**	parse.c
*/
char			*comment_command(t_file *file);
char			*get_name(char *line);
void			get_ants(t_file *file);
void			parse(t_file *file);

/*
**	tools.c
*/
void			rooms_exist(t_file *file, char *r1, char *r2);
void			add_room_path(t_file *file, t_path *head, char *name);
t_room			*find_room(t_file *file, char *to_find);
int				room_pos(t_file *file, char *to_find);

/*
**	utilities.c
*/
void			error(int errno);
char			*colorsfind(t_file *file, char *command);

/*
**	connection.c
*/
int				if_connect(t_file *file, int i);
int				check_row(t_file *file, int i, char *to_compare, int w);
void			add_room(int weight, char *name, t_room *prev);
void			make_connect(t_file *file, char *r1, char *r2, int i);
void			connect(t_file *file);

/*
**	rooms.c
*/
void			rooms(t_file *file, int i);
int				if_room(char *line, int i);

/*
**	read.c
*/
char			*readandstore(void);
int				gnl(t_file *file);

/*
**	solve.c
*/
int				find_path(t_file *file, t_room *ptr, int w);
void			solve(t_file *file);
void			save_path(t_file *file);

/*
**	free.c
*/
void			free_file(t_file *file);
void			free_paths(t_file *file);
void			free_rooms(t_file *file);

/*
**	print.c
*/
void			move_ants(t_file *file, int cycle, int i, int paths);
void			display_ants(t_file *file, int cycle, int paths);
int				print_path(t_file *file);
void			count_ants(t_file *file, int first_index, int ants, int i);
void			get_paths(t_file *file, int path, int i);

#endif
