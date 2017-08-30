/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/08/30 14:08:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int		sus_pid(t_job **job, t_ast **ast, t_job **table)
{
	int			i;
	t_job		*j;
	t_process	*p;

	(void)job;
	(void)ast;
	if (*table)
	{
		i = 1;
		j = *table;
		if (j)
		{
			ft_putendl_fd("AE", 2);
			while (j && !(j->first_process->stopped != 1 && j->first_process->completed != 1))
			{
				j = j->next;
				i++;
			}
			if (j)
			{
				ft_putendl_fd("B", 2);
				ft_printf("[%d]+  Stopped			%s\n", i, j->command);
				ft_putendl_fd("C", 2);
				p = j->first_process;
				ft_putendl_fd("D", 2);
				while (p)
				{
					p->stopped = 1;
					kill(p->pid, SIGTSTP);
					p = p->next;
				}
				ft_putendl_fd("E", 2);
			}
		}
	}
	return (1);
}
// int		sus_pid(t_job **job, t_ast **ast, t_job **table)
// {
// 	int			nbjob;
// 	t_job		*head;
// 	t_process	*phead;
//
// 	(void)job;
// 	(void)ast;
// 	nbjob = 1;
// 	if (!(*table))
// 		return (0);
// 	head = (*table);
// 	phead = (*table)->first_process;
// 	while ((*table)->next)
// 	{
// 		(*table) = (*table)->next;
// 		nbjob++;
// 	}
// 	if ((*table)->first_process->stopped != 1)
// 	{
// 		phead = (*table)->first_process;
// 		printf("[%d]+  Stopped			%s\n", nbjob, (*table)->command);
// 		while ((*table)->first_process)
// 		{
// 			(*table)->first_process->stopped = 1;
// 			kill((*table)->first_process->pid, SIGTSTP);
// 			(*table)->first_process = (*table)->first_process->next;
// 		}
// 		(*table)->first_process = phead;
// 	}
// 	(*table) = head;
// 	return (1);
// }

void	wait_for_job(t_job **job)
{
	pid_t		pid;
	int			status;

	while (!job_is_stopped(*job) && !job_is_complete(*job))
	{
		ft_putendl("A");
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WCONTINUED);
		if (mark_job_status(job, status, pid) == 0)
			break ;
	}
}

void	mark_job_as_running(t_job **job)
{
	t_process	*p;

	p = (*job)->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
}

int		foreground(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_process	*p;
	(void)job;
	(void)ast;

	ft_putendl("WTF");
	if (*table)
	{
		j = *table;
		while (j->next)
			j = j->next;
		p = j->first_process;
		mark_job_as_running(&j);
		print_job(&j);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
		// setpgid(g_shell_pgid, j->pgid);
		tcsetpgrp (g_shell_terminal, j->pgid);
		// tcsetattr (g_shell_terminal, TCSADRAIN, &j->tmodes);
		while (p)
		{
			kill(p->pid, SIGCONT);
			p = p->next;
		}
		wait_for_job(&j);
		// mark_process_status(&j);
		// tcgetattr (g_shell_terminal, &j->tmodes);
		/* Restore the shell’s terminal modes.  */
		// ft_putnbrl(g_shell_pgid);
		tcsetpgrp (g_shell_terminal, g_shell_pgid);
		tcsetattr (g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
		//init_shell();
		signal(2, cmdl_ctrc);
		signal(21, canon_mode);
		signal(28, cmdl_wins);
		signal(18, ctrl_z);
		return (1);
	}
	return (0);
}
