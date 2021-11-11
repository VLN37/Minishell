/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_translate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:56:07 by jofelipe          #+#    #+#             */
/*   Updated: 2021/11/11 20:16:58 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_single_quotes(t_pat *pat, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
			while (cmd[i][j])
			{
				if (cmd[i][j] == SQUOTES)
				{
					cmd[i] = single_quotes(pat, cmd[i], j);
					j = 0;
				}
				++j;
			}
		j = 0;
		++i;
	}
}

void	printcmd(char ***cmd)
{
	int	i;
	int	j;

	i = -1;
	j = -1;

	while (cmd[++i])
	{
		while (cmd[i][++j])
			ftex_minprintf("%s\n", cmd[i][j]);
		j = -1;
	}
}

char	*replace_env(char *cmd)
{
	int		i;
	char	*env;
	char	*envvalue;

	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '$')
		{
			env = ft_substr(cmd, i, envlen(&cmd[i]));
			envvalue = getenv(&env[1]);
			if (!envvalue)
				envvalue = ft_strdup("");
			ftex_minprintf("env: %s\n", env);
			ftex_minprintf("evnvalue: %s\n", envvalue);
			cmd = ftex_str_replace(cmd, env, envvalue);
			ftex_minprintf("cmd after env: %s\n", cmd);
			// free(env);
			// free(envvalue);
		}
		i++;
	}
	return (cmd);
}

char	***find_env(char ***cmd)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	ftex_minprintf("\n======= FIND ENV ======\n\n");
	printcmd(cmd);
	ftex_minprintf("\n\n\n=============\n");
	while (cmd[++i])
	{
		while (cmd[i][++j])
		{
			if (ft_strchr(cmd[i][j], '$'))
			{
				ftex_minprintf("|%s|\n", cmd[i][j]);
				cmd[i][j] = replace_env(cmd[i][j]);
				j = -1;
			}
		}
		j = -1;
	}
	return (cmd);
}

char	***translate(t_pat *pat, char ***cmd, char **envp)
{
	int	i;

	i = -1;
	pat->i = 0;
	printf("%d\n", pat->i);
	while (cmd[++i])
		replace_single_quotes(pat, cmd[i]);
	printcmd(cmd);
	cmd = find_env(cmd);
	ft_putstr_fd("here\n", 1);
	if (DEBUG)
	{
		ftex_minprintf("here\n");
		ftex_minprintf("\n===== TRANSLATE ======\n");
		printcmd(cmd);
		ftex_minprintf("\n");
	}
	cmd = restore_quoted(pat, cmd);
	return (cmd);
}
