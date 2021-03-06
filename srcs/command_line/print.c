/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:59:44 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/15 13:04:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	clear_comp(t_cmdl *cmdl)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	end(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	cmdl->opt &= ~(CCOMP);
	comp_del(&cmdl->comp);
	cmdl->offset = -1;
}

static int	cmode(t_cmdl *cmdl)
{
	int		cur_save;

	if (cmdl->line.buf[0] != 'y' && cmdl->line.buf[0] != 'n')
		return (write(2, "\7", 1));
	else if (cmdl->line.buf[0] == 'y')
		print_comp(&cmdl->comp);
	else
		write(1, "\n", 1);
	cur_save = cmdl->line.cur - cmdl->line.pr;
	cmdl->opt &= ~(CCMODE | CCOMP);
	print_prompt();
	cmdl->line.pr = 3;
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	while ((cmdl->line.cur - cmdl->line.pr) > cur_save)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		cmdl->line.cur--;
	}
	comp_del(&cmdl->comp);
	return (1);
}

void		remalloc_cmdl(t_line *line)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (line->len + line->len))))
		exit(0);
	ft_memset(tmp, 0, (line->len + line->len));
	tmp = ft_strcpy(tmp, line->str);
	ft_strdel(&line->str);
	line->str = tmp;
	line->len += line->len;
}

int			regular_print(t_line *line, char buf[], int i, int j)
{
	int		len;

	len = ft_strlen(line->str);
	if (len + line->pr >= line->co * line->li - (line->co + 1) &&
	write(2, "\7", 1))
		return (-1);
	len == (line->len - 1) ? remalloc_cmdl(line) : 0;
	if (line->str[i] == 0)
		line->str = ft_strcat(line->str, buf);
	else
	{
		j = len;
		while (j-- > i)
			line->str[j + 1] = line->str[j];
		line->str[i] = buf[0];
	}
	PRINT(buf) ? write(1, line->str + i, 1) : 0;
	PRINT(buf) ? write(1, line->str + i + 1, ft_strlen(line->str + i + 1)) : 0;
	line->cur += ft_strlen(line->str + i);
	!(line->cur % line->co) ? tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
	return ((i += (len = (int)ft_strlen(line->str) - len) > 1 ? len : 0));
}

int			print(t_cmdl *cmdl, char buf[])
{
	int		i;

	if (!(PRINT(buf)) && !(SH(buf)))
		return (1);
	if (ft_strlen(buf) > 1)
		return (graphical_print(cmdl, buf));
	if (cmdl->opt & CCP)
		return (write(2, "\7", 1));
	if (PRINT(buf) && (cmdl->opt & CCOMP) && !(cmdl->opt & CCMODE))
		clear_comp(cmdl);
	else if (cmdl->opt & (CCOMP | CCMODE) && cmode(cmdl))
		return (1);
	if (PRINT(buf) && !(cmdl->opt & CHIS_S))
	{
		if ((i = regular_print(&cmdl->line, buf,
		(cmdl->line.cur - cmdl->line.pr), 0)) >= 0)
		{
			cmdl->opt &= ~(CCOMP);
			while (cmdl->line.cur - cmdl->line.pr - 1 > i)
				arrow_left(cmdl);
		}
	}
	else if (cmdl->opt == CHIS_S)
		search_history_print(cmdl, buf);
	return (1);
}
