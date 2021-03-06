/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_translate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:56:07 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/20 16:50:32 by jofelipe         ###   ########.fr       */
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
			if (cmd[i][j] == DQUOTES)
			{
				++j;
				while (cmd[i][j] != DQUOTES && cmd[i][j] && cmd[i][j + 1])
					++j;
			}
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

char	*replace_env(char *cmd, char **envp)
{
	int		i;
	char	*env;
	char	*envvalue;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] != ' ')
		{
			env = ft_substr(cmd, i, envlen(&cmd[i]));
			envvalue = get_env_val(&env[1], envp);
			if (!envvalue)
				envvalue = ft_strdup("");
			cmd = ftex_str_replace(cmd, env, envvalue);
			i = -1;
			free(env);
			free(envvalue);
		}
	}
	return (cmd);
}

void	find_env(char ***cmd, char **envp)
{
	int		i;
	int		j;
	char	*dollar;

	i = -1;
	j = -1;
	while (cmd[++i])
	{
		while (cmd[i][++j])
		{
			if (ft_strchr(cmd[i][j], '$'))
			{
				cmd[i][j] = replace_env(cmd[i][j], envp);
				dollar = ft_strchr(cmd[i][j], '$');
				if (!dollar)
					j = -1;
			}
			else if (!ft_strncmp(cmd[i][j], "~", ft_strlen(cmd[i][j])))
				cmd[i][j] = replace_home(cmd[i][j], "~");
			else if (!ft_strncmp(cmd[i][j], "~/", 2))
				cmd[i][j] = replace_home(cmd[i][j], "~");
		}
		j = -1;
	}
	return ;
}

void	translate(t_pat *pat, char ***cmd, char **envp)
{
	int	i;

	i = -1;
	while (cmd[++i])
		replace_single_quotes(pat, cmd[i]);
	find_env(cmd, envp);
	if (DEBUG)
	{
		ftex_minprintf("\n===== TRANSLATE ======\n");
		printcmd(cmd);
		ftex_minprintf("\n");
	}
	restore_quoted(pat, cmd);
	trim_quotes(cmd);
	return ;
}
