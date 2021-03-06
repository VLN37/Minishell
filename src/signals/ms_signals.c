/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 07:33:05 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/14 05:12:53 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_env_val("?", "130", g_envp);
	}
}

void	sig_child(int sig)
{
	if (sig == SIGINT)
	{
		fd_collector();
		exit(130);
	}
	if (sig == SIGQUIT && inside_here_doc() == false)
	{
		fd_collector();
		exit(131);
	}
}

void	sig_cmd(int sig)
{
	char	str[100];
	int		i;

	i = -1;
	while (++i < 2)
		str[i] = 8;
	str[i] = 0;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		set_env_val("?", "130", g_envp);
	}
	if (sig == SIGQUIT && inside_here_doc() == true)
	{
		ft_putstr_fd(str, 1);
		write(1, "  ", 2);
		ft_putstr_fd(str, 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit", 2);
		set_env_val("?", "131", g_envp);
	}
}

void	init_sigaction(t_sigaction *action, void (*handler)(int), int sig)
{
	action->sa_handler = handler;
	action->sa_flags = SA_RESTART;
	sigemptyset(&action->sa_mask);
	sigaction(sig, action, NULL);
}
