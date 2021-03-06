/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jonathan_kent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:40:06 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 12:30:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_quote(t_tok **lst, char **stack, char *line, int *i)
{
	int		type;
	char	quote;

	quote = line[(*i)++];
	type = (quote == '\'' ? QUOTE : DQUOTE);
	in_quote(stack, line, i, quote);
	if (line[(*i)] && !is_space(line[(*i)]) &&
			line[(*i)] != '"' && line[(*i)] != '\'' && is_sep(line[(*i)]) != 1)
		after_quote(stack, line, i);
	if (line[(*i)] && (line[(*i)] == '\'' || line[(*i)] == '"'))
		stuck_quote(stack, line, i);
	tok_save(lst, stack, QUOTE);
	if (line[(*i)] && line[(*i) + 1] && check_end(line + ((*i) + 1)))
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	(*i)--;
}

void	chevron(t_tok **lst, char **stack, char *line, int *i)
{
	int					j;
	static const t_che	key[3] = {{'>'}, {'<'}, {'&'}};

	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, io_number(*stack) ? IO_N : WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)++], 0);
	j = -1;
	while (++j < 3)
		if (line[(*i)] == key[j].c &&
			((*stack)[0] == key[j].c || line[(*i)] == '&'))
		{
			st_tok(stack, line[(*i)], 0);
			break ;
		}
	j == 3 ? (*i)-- : (*i);
	tok_save(lst, stack, CHEVRON);
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
}

void	question_mark(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)], 0);
	tok_save(lst, stack, QM);
	if (check_end(line + (*i) + 1) == 1)
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
}

void	pipe_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)], 0);
	if (line[(*i) + 1] == '|')
	{
		st_tok(stack, line[++(*i)], 0);
		tok_save(lst, stack, OR);
	}
	else
		tok_save(lst, stack, PIPE);
	if (check_end(line + (*i) + 1))
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
}

void	and_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)], 0);
	if (line[(*i) + 1] == '&')
	{
		st_tok(stack, line[++(*i)], 0);
		tok_save(lst, stack, AND);
	}
	else
		tok_save(lst, stack, BGE);
	if (check_end(line + (*i) + 1) == 1)
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
}
