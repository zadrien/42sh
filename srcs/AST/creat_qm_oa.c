/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_qm_oa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 10:40:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/17 18:12:41 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_tok	*find_tok(t_tok **lst, t_tok **sep, t_tok **new_sep, int i)
{
	t_tok	*tmp;

	tmp = *lst;
	if (i == 0)
	{
		while (tmp && (tmp->type != QM) && tmp != *sep)
			tmp = tmp->n;
		if (tmp == *sep)
			return (tmp);
		(*lst) = tmp->n;
		(*new_sep) = tmp;
		return (tmp->n);
	}
	else
	{
		while (tmp && tmp != *sep && (tmp->type != AND && tmp->type != OR))
			tmp = tmp->n;
		if (tmp == *sep)
			return (tmp);
		(*lst) = tmp->n;
		(*new_sep) = tmp;
		return (tmp->n);
	}
}

void			qm_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_tok	*new_sep;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	tmp_first = *lst;
	while ((tmp = find_tok(&tmp_first, sep, &new_sep, 0)) != *sep)
		;
	if (tmp_first != *lst)
	{
		init_ast(&tmp_ast->left, &new_sep, new_sep->type);
		tmp_ast = tmp_ast->left;
		init_ast(&tmp_ast->right, NULL, 0);
		secondary_sequence(&tmp_ast->right, &tmp_first, &tmp);
		qm_sequence(&tmp_ast, lst, &new_sep);
	}
	else
	{
		init_ast(&tmp_ast->left, NULL, 0);
		secondary_sequence(&tmp_ast->left, lst, sep);
	}
}

void			oa_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_tok	*new_sep;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	tmp_first = *lst;
	while ((tmp = find_tok(&tmp_first, sep, &new_sep, 1)) != *sep)
		;
	if (tmp_first != *lst)
	{
		init_ast(&tmp_ast->left, &new_sep, new_sep->type);
		tmp_ast = tmp_ast->left;
		init_ast(&tmp_ast->right, NULL, 0);
		tertiary_sequence(&tmp_ast->right, &tmp_first, &tmp);
		oa_sequence(&tmp_ast, lst, &new_sep);
	}
	else
	{
		init_ast(&tmp_ast->left, NULL, 0);
		tertiary_sequence(&tmp_ast->left, lst, sep);
	}
}
