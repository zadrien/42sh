/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_fucn2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 16:07:10 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/13 09:26:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			opt_left(t_cmdl *cmdl)
{
	if (cmdl->opt & (CCMODE | CCOMP | CHIS_S))
		return (write(2, "\7", 1));
	if (cmdl->line.str[0])
	{
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != ' ' &&
		cmdl->line.cur > cmdl->line.pr)
			arrow_left(cmdl);
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] == ' ' &&
		cmdl->line.cur > cmdl->line.pr)
			arrow_left(cmdl);
	}
	return (1);
}

int			opt_right(t_cmdl *cmdl)
{
	if (cmdl->opt & (CCMODE | CCOMP | CHIS_S))
		return (write(2, "\7", 1));
	if (cmdl->line.str[0])
	{
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != ' ' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != 0)
			arrow_right(cmdl);
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] == ' ' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != 0)
			arrow_right(cmdl);
	}
	return (1);
}
