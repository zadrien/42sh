/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:57:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 12:59:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_free(char *tab[], char **line, int w)
{
	int			i;

	i = -1;
	if (tab)
	{
		if (w == 2 || w == 3)
			ft_strdel(line);
		if (w == 1 ||  w == 3)
		{
			while (tab[++i])
				tab[i] ? ft_strdel(&tab[i]) : 0;
			free(tab);
		}
	}
	return (1);
}
