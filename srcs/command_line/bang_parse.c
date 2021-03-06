/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 18:21:27 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 18:56:06 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_modifiers(char *event, t_bang *bang)
{
	event[0] == 'h' ? bang->mod |= HB : 0;
	event[0] == 't' ? bang->mod |= TB : 0;
	event[0] == 'r' ? bang->mod |= RB : 0;
	event[0] == 'e' ? bang->mod |= EB : 0;
	event[0] == 'p' ? bang->mod |= PB : 0;
	event[0] == 'q' ? bang->mod |= QB : 0;
	event[0] == 'x' ? bang->mod |= XB : 0;
	if (!ft_strchr("htrepqx", event[0]))
	{
		return (fd_printf(2, "\n42sh: %c: unrecognized history modifier",\
		event[0]));
	}
	return (0);
}

int		get_designators(char *event, t_bang *bang, int max_arg)
{
	char	*ptr;

	if (event[0] >= '0' && event[0] <= '9' && !ft_strchr(event, '-') &&
	!ft_strchr(event, '*'))
		bang->des = ft_atoi(event);
	else if (event[0] == '^' || event[0] == '$')
		bang->des = event[0] == '^' ? 1 : max_arg;
	else if ((ptr = ft_strchr(event, '-')))
	{
		if (bang_range(bang, event, ptr, max_arg))
			return (1);
	}
	else if (ft_strchr(event, '*'))
	{
		bang->x = event[0] == '*' ? 1 : ft_atoi(event);
		bang->y = max_arg;
	}
	else
		return (fd_printf(2, "\n42sh: !%s: event not found", event));
	bang->mod |= 128;
	return (0);
}

int		get_event(char *cmdl, t_bang *bang)
{
	char	**qsub;

	if (cmdl[0] >= '0' && cmdl[0] <= '9')
		bang->n = ft_atoi(cmdl);
	else if (cmdl[0] == '-' && cmdl[1] && cmdl[1] >= '0' && cmdl[1] <= '9')
		bang->n = -(ft_atoi(cmdl + 1));
	else if (cmdl[0] == '!')
		bang->n = -1;
	else if (cmdl[0] == '?' && (bang->qm = 1))
		bang->string = cmdl + 1;
	else if (cmdl[0] == '^')
	{
		if ((qsub = ft_strsplit(cmdl, '^')) && !qsub[0])
			return (fd_printf(2, "\n42sh: %s: no previous substitution", cmdl));
		bang->s1 = ft_strdups(qsub[0], &bang->s1);
		bang->s2 = qsub[1] ? ft_strdups(qsub[1], &bang->s2) : NULL;
		ft_free(qsub, NULL, 1);
	}
	else if (ft_isalpha(cmdl[0]))
		bang->string = cmdl;
	else
		return (fd_printf(2, "\n42sh: !%s: event not found", cmdl));
	return (0);
}

int		bang_parse(char *sub, t_bang *bang)
{
	t_his		*his;
	char		**opt;

	if (!sub)
		return (1);
	opt = ft_strsplit(sub, ':');
	if (!(his = (*his_slg())->n))
		return (bang_error(sub, opt));
	if (call_get_event(bang, his, opt, &sub))
		return (1);
	if (call_get_designators(bang, his, opt, &sub))
		return (1);
	if (call_get_modifiers(bang, opt, &sub))
		return (1);
	if (sub[0] != '^' && bang_sub(bang))
		return (ft_free(opt, &sub, 3));
	ft_free(opt, &sub, 3);
	return (0);
}
