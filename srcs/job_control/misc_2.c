/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:43:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:46:48 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		countnode(t_env *env)
{
	int		i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*var_value(int i, char *var, char *value)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, var);
	ft_strcat(str, "=");
	value ? ft_strcat(str, value) : 0;
	return (str);
}

void	stock_restore(int mod)
{
	static int		stdin = -1;
	static int		stdout = -1;
	static int		stderr = -1;

	if (mod)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else
	{
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		dup2(stderr, STDERR_FILENO);
		close(stdin);
		close(stdout);
		close(stderr);
	}
}
