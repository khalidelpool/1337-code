/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:48:32 by kel-mous          #+#    #+#             */
/*   Updated: 2024/12/21 19:50:16 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*compute(char **str, int fd);
char	*ftg_split(char **str, int position);
char	*ftg_strjoin(char *str, char *buff);
char	*ftg_strdup(const char *s, int start, int length);
size_t	ftg_strlen(const char *s);
void	*ftg_memcpy(void *dest, const void *src, size_t n);
int		ft_findchar(char *str, char to_find, int *len);
void	ftg_bzero(void *s, size_t n);
void	*ftg_calloc(size_t nmemb, size_t size);

#endif
