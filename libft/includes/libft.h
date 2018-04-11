/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 18:35:16 by psprawka          #+#    #+#             */
/*   Updated: 2017/09/20 18:35:20 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

long int		ft_atoi(char *s);
char			*ft_ftoa(double n);
char			*ft_itoa(int nbr);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *src);
int				ft_strlen(char *str);
void			ft_bzero(void *s, unsigned int n);
char			*ft_strnew(size_t size);
void			*ft_memset(void *s, int c, size_t n);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen_chr(char *str, char c);
char			*ft_strncpy(char *str, int size);
int				ft_strstr(char *str, char *to_find);

int				ft_wstrlen(wchar_t *ws);
char			*ft_strrev(char *str);
void			*ft_memalloc(size_t size);
char			*ft_convert_hex(unsigned long int nb, int type);
char			*ft_convert_octal(unsigned long int nb);
char			*ft_convert_uni(wchar_t wide);
int				ft_printf(const char *format, ...);

#endif
