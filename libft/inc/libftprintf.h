/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 14:58:14 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 14:02:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include "../get_next_line/get_next_line.h"
# include "../printf/printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *dst, char *src, size_t size);

void				ft_streplace(char **str, char c, char r);
void				ft_free(char ***tab, char **line);
void				display_int_tab(int **tab);
void				ft_putnbrl(int c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t len);
int					ft_putchar(int c);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void(*f)(char*));
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putstr_long(long long int n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstdelone(t_list **alst, void(*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void(*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_putendl(char const *s);
void				ft_sort_int_tab(int *tab, int size);
void				ft_puthexa(void);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_display_tab(char **tab);

size_t				ft_intlen(size_t nbr);
int					ft_tablen(char **tab);
int					get_next_line(const int fd, char **line);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char*s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_isupper(char c);
int					ft_iterative_power(int nb, int power);
int					ft_iterative_factorial(int nb);
int					convert_to_d(char *tab, int base);

char				*ft_strdup(const char *src);
char				*ft_strdupf(char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char*s2, size_t n);
char				*ft_strstr(const char *s1, const char *to_find);
char				*ft_strnstr(const char *s1, const char *to_find,
		size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa_base(long long int n, int base);
char				*ft_itoa(int n);
char				*ft_strtrim(char const *s);
char				*ft_strrev(char *str);
char				*ft_strjoinf(char *s1, char *s2, int w);
char				*ft_strat(char **env, int i);
char				*ft_strtrimf(char *s);
char				*ft_strenv(char *s1, char *s2);

void				ft_errormsg(char *env, char *cmd, char *str); // Maybe to delete
void				ft_putendn(int i);
#endif