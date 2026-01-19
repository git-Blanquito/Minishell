/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:04:16 by aiblanco          #+#    #+#             */
/*   Updated: 2025/10/17 21:01:33 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <stdint.h>// SIZE MAX
# include <fcntl.h>//Argumentos función Open
# include <unistd.h>//Write y Open
# include <stdio.h>//Null y printf
# include <stdlib.h>//Malloc y free
# include <string.h>//Null y size-t
# include <limits.h>//OPEN_MAX para generar el numero de posiciones maximo
# include "stdarg.h"//Argumentos infinitos para funciones 

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, int n);
void	*ft_memcpy(void *dst, const void *src, int n);
void	*ft_memmove(void *dst, const void *src, int len);
int		ft_strlcpy(char *dst, const char *src, unsigned int dstsize);
int		ft_strlcat(char *dst, const char *src, unsigned int dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
void	*ft_memchr(const void *s, int c, int n);
int		ft_memcmp(const void *s1, const void *s2, int n);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t j);
char	*ft_substr(const char *src, unsigned int m, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *newe);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newe);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//Printf
int		ft_printf(char const *str, ...);
void	ft_printhex(unsigned int num, int *pcharcount, char c);
void	ft_printunnum(unsigned int num, int *pcharcount);
void	ft_printnum(int num, int *pcharcount);
void	ft_printptr(unsigned long long num, int *pcharcount);
void	ninehex(unsigned long long num, int *pcharcount);
int		ft_printstr(char *str, int *pcharcount);
void	ft_printchar(int character, int *pcharcount);

//GetNextLine
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
size_t	strleng_gnl(const char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	*freeft(char *str);

//newfunctions
int		ft_isnumber(const char *str);
long	ft_atol(const char *str);

#endif