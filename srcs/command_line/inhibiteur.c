/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibiteur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:20:06 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/09 17:52:21 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		inhibiteur(t_cmdl *cmdl, int len)
{
	int		count;

	count = 0;
	while (cmdl->line.str[len] == '\\' && len >= 0)
	{
		count++;
		len--;
	}
	if ((count % 2))
	{
		write(1, "\n$> ", 4);
		cmdl->line.cur = 3;
		cmdl->line.pr = 3;
		return (1);
	}
	return (0);
}
