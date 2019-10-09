/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:08:26 by jandreu           #+#    #+#             */
/*   Updated: 2017/12/01 21:15:36 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFF_SIZE 10

typedef u_int64_t	uint64_t;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_read_tab(char **tab);
int					ft_count_line(int fd);
int					get_next_line(int const fd, char **line);
void				ft_putchar(char c);
void				ft_putstr(char const *c);
size_t				ft_strlen(char const *c);
char				*ft_strcpy(char *dest, char const *src);
void				ft_putnbr(int n);
void				ft_putendl(char const *s);
void				ft_strclr(char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(char const *s1);
char				*ft_strncpy(char *dst, char const *src, size_t n);
char				*ft_strcat(char *dst, char const *src);
char				*ft_strncat(char *dst, char const *src, size_t n);
char				*ft_strstr(char *s1, char *s2);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(char const *str);
char				*ft_strrchr(char const *s, int c);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void*s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f) (char));
void				ft_striter(char *s, void (*f)(char *));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_itoa_hex(uint64_t n, int is_upcase, char *buff);
void				ft_put_addr(void *addr);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
#endif
