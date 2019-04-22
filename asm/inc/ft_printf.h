/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:08:54 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:47:49 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <inttypes.h>
# define MALLOC_CHECK_NULL(x) if (!(x)) return (NULL)

typedef	struct	s_struct
{
	int			plus_or_space;
	int			is_left_just;
	int			is_octotorp;
	int			is_prezero;
	int			width;
	int			acc;
	char		size;
	char		spec;
	int			len;
}				t_arg_info;

int				ft_printf(char *s, ...);
char			*h_num(t_arg_info info, va_list lst);
char			*h_acc(t_arg_info info, char *str);
char			*h_plus_or_space(char *out, t_arg_info info);
long long		h_width(t_arg_info info, char *str);
char			*ft_itoa_base(uintmax_t num, int base);
char			*ft_strrev(char *str, int triger);
char			*ft_itoa_u(uintmax_t n);
char			*ft_itoa_s(intmax_t n);
char			*h_octotorp(t_arg_info info, char *str);
char			*h_float(t_arg_info info, va_list lst);
char			save_spec(char *str);
int				save_width(char *str);
char			save_size(char *str);
size_t			get_arg_num(char *s);
int				save_acc(char *str);
char			*handle_wchar(unsigned int x);
int				handle_char(char c, t_arg_info info);
char			*h_wstring(unsigned int *tab, t_arg_info info);
int				is_spec(char i);
int				is_valid(char c);
char			*get_s_from_c(t_arg_info info);
void			save_flag(char *str, t_arg_info *format);
char			*ft_strjoin_deluxe(char *s1, char *s2, int triger);
char			*ft_push_start(char c, char *s, int acc);

#endif
