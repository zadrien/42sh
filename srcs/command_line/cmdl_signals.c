/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:26:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 14:55:14 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 	handle_ctrlc(t_cmdl *cmdl)
{
	char	*tmp;

	cmdl->ccp.start = -1;
	tputs(tgetstr("me", NULL), 1, ft_putchar);
	!(cmdl->opt & CHIS_S) ? end(cmdl) :
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	!(cmdl->opt & CHIS_S) ? write(1, "\n", 1) : 0;
	!(cmdl->opt & CHIS_S) ? print_prompt() : write(1, "$> ", 3);
	cmdl->opt = 0;
	cmdl->opt |= CRESET;
	if (cmdl->line.save)
	{
		tmp = ft_strdup(cmdl->line.str);
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		while ((int)ft_strlen(cmdl->line.save) > cmdl->line.len)
			remalloc_cmdl(&cmdl->line);
		cmdl->line.str = ft_strcpy(cmdl->line.str,cmdl->line.save);
		cmdl->line.str = ft_strcat(cmdl->line.str, tmp);
		ft_strdel(&tmp);
	}
	if (cmdl->opt & (CSQ | CDQ | CPIPE | CAND | COR))
		cmd_save_history(cmdl->line.str);
	cmd_history(cmdl);
	init_cmdl();
}

static void		sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_cmdl		*cmdl;

	(void)siginfo;
	(void)context;
	cmdl = *cmdl_slg();
	if (sig == SIGWINCH)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar);
		get_win_data(cmdl);
		print_prompt();
		ft_putstr(cmdl->line.str);
		cmdl->opt & CCOMP ? display_comp(cmdl, &cmdl->comp, 0) : 0;
	}
	else if (sig == SIGINT)
		handle_ctrlc(cmdl);
	else if (sig == SIGQUIT)
	{
		del_all(cmdl_slg(), his_slg(), local_slg(0));
		exit(EXIT_SUCCESS);
	}
}

void			cmdl_signals(t_cmdl *cmdl)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_sigaction = &sig_handler;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGWINCH, &sig, NULL) == -1 ||
		sigaction(SIGINT, &sig, NULL) == -1 ||
		sigaction(SIGQUIT, &sig, NULL) == -1)
	{
		unset_shell(cmdl);
		exit(fd_printf(2, "cmdl_signals: sigaction error\n"));
	}
}
