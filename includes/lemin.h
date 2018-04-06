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

# define BUFF_SIZE 		100
# define MAX_NAME_LEN 	1000
# define MAX_PATHS_NB	100000
# define MAX_ROOMS_NB	100000

# define NORMAL		"\x1B[0m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGNETA	"\x1B[35m"
# define CYAN		"\x1B[36m"


typedef struct  s_room
{
    struct s_room   *next;
    char            *name;
    int             weight;
	int				path;
	int				open;
    
}               t_room;

typedef struct  s_file
{
    int             ants;
	int				nb_paths;
	char			**paths;
    char            *map;
    char            *line;
    struct s_room   **rooms;
	struct s_room   **final_paths;
	int				nb_rooms;
    char            *start;
    char            *end;
	int				offset;
    
}               t_file;

# define ROOMS			file->rooms

/* libft.c */
long int	ft_atoi(char *s);
char    	*ft_itoa(int nbr);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *src);
int			ft_strlen(char *str);
void    	ft_bzero(void *s, unsigned int n);
char		*ft_strnew(size_t size);
void		*ft_memset(void *s, int c, size_t n);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen_chr(char *str, char c);
char		*ft_strncpy(char *str, int size);
int			ft_strstr(char *str, char *to_find);

/* parse.c */
char	*get_name(char *line);
void	get_ants(t_file *file);
void	comment_command(t_file *file);
void    parse(t_file *file);

/* tools.c */
void	error(void);

/* connection.c */
int		if_connect(t_file *file, int i);
int		check_row(t_file *file, int i, char *to_compare, int w);
void	add_room(int weight, char *name, t_room *prev);
void	make_connect(t_file *file, char *r1, char *r2);
void	connect(t_file *file);

/* rooms.c */
void	rooms(t_file *file);
int 	if_room(char *line, int i);

/* read.c */
char    *readandstore(void);
int		gnl(t_file *file);

/* solve.c */
t_room	*find_room(t_file *file, char *to_find);
int		room_pos(t_file *file, char *to_find);
int		find_path(t_file *file, t_room *ptr, int w);
void	solve(t_file *file);
void	save_path(t_file *file);

/* free.c */
void	free_file(t_file *file);
void	free_paths(t_file *file);
void	free_rooms(t_file *file);

/* print.c */
int 	print_path(t_file *file);

#endif
