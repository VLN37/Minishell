/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wleite <wleite@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 00:52:08 by jofelipe          #+#    #+#             */
/*   Updated: 2021/11/11 19:01:02 by wleite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alt_unset(char *str)
{
	ftex_minprintf("%s", str);
}

void	alt_exit(char *str)
{
	ftex_minprintf("%s", str);
}
