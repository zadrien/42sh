/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:43:02 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 10:50:16 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	if (n == 0 || !s2)
		return (0);
	i = -1;
	while (s1[++i] && s1[i] == s2[i] && i < n - 1)
		;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
