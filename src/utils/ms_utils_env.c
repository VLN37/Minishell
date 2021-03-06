/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wleite <wleite@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:33:32 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/17 16:28:18 by wleite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_status_code(char **envp)
{
	int		status_code;
	char	*tmp;

	tmp = get_env_val("?", envp);
	status_code = ft_atoi(tmp);
	ftex_null_ptr((void *)&tmp);
	return (status_code);
}

void	set_env(char *var, char *value, char **envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!ft_strncmp(var, tmp[0], ft_strlen(var))
			&& !ft_strncmp(var, tmp[0], ft_strlen(tmp[0])))
		{
			ftex_null_ptr((void *)&envp[i]);
			envp[i] = ft_strdup(value);
			free_splited_mat(tmp);
			return ;
		}
		free_splited_mat(tmp);
	}
	envp[i] = ft_strdup(value);
	envp[i + 1] = NULL;
}

char	*get_env(char *value, char **envp)
{
	int		i;
	char	**tmp;

	if (!value || !*value)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!ft_strncmp(value, tmp[0], ft_strlen(value))
			&& !ft_strncmp(value, tmp[0], ft_strlen(tmp[0])))
		{
			free_splited_mat(tmp);
			return (ft_strdup(envp[i]));
		}
		free_splited_mat(tmp);
	}
	return (NULL);
}

char	*get_env_val(char *value, char **envp)
{
	int		i;
	char	*val;
	char	**tmp;

	if (!value || !*value)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!ft_strncmp(value, tmp[0], ft_strlen(value))
			&& !ft_strncmp(value, tmp[0], ft_strlen(tmp[0])))
		{
			val = ft_strdup(tmp[1]);
			free_splited_mat(tmp);
			return (val);
		}
		free_splited_mat(tmp);
	}
	return (NULL);
}

void	set_env_val(char *var, char *value, char **envp)
{
	int		i;
	char	*val;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!ft_strncmp(var, tmp[0], ft_strlen(var))
			&& !ft_strncmp(var, tmp[0], ft_strlen(tmp[0])))
		{
			ftex_null_ptr((void *)&envp[i]);
			val = ft_strjoin(var, "=");
			envp[i] = ftex_strmerge(val, ft_strdup(value));
			free_splited_mat(tmp);
			return ;
		}
		free_splited_mat(tmp);
	}
	val = ft_strjoin(var, "=");
	envp[i] = ftex_strmerge(val, ft_strdup(value));
	envp[i + 1] = NULL;
}
