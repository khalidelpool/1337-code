/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:07:02 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 01:07:07 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>

# define READ 0
# define WRITE 1
# define CURR 0
# define PREV 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*init_back_node(t_list **lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
void	ft_putstr(char *str, int fd);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_append(char **org, char c, int position);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_strjoin_px(char **str, char *buff, int choice);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*get_path(char **envp);
int		arr_size(char **ptr);
char	**get_array(char *cmd);

void	del(void *content);
void	free_arr(char ***ptr);
void	close_fds(int *pipe_fd);
int		at(int i, int state, int wr);
void	free_size(char ***ptr, int size);
void	cleanup(int i, int *pip, char *av, pid_t id);

#endif
