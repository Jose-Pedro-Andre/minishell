/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 04:58:30 by joandre           #+#    #+#             */
/*   Updated: 2024/12/06 07:44:17 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_very_and_bar(char *path)
{
	char	*w;
	size_t	len;

	len = ft_strlen(path);
	w = malloc(len + 2);
	if (!w)
	{
		return (NULL);
	}
	ft_strcpy(w, path);
	ft_strcat(w, "/");
	return (w);
}

void	ft_current_dir(t_master *master, char **av)
{
	char	*cmd;
	char	*path;
	char	*get;
	int		len;
	int		cwd;

	get = getcwd(NULL, 0);
	cmd = av[0];
	cwd = ft_strlen(get);
	len = ft_strlen(cmd);
	path = malloc(cwd + len + 2);
	ft_strlcpy(path, get, cwd + 1);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	if (execv(path, av) == -1)
	{
		print_default_fd(master, ft_strjoin("command not found: ", av[0]));
		printf("\n");
		free(path);
		free(get);
		exit(127);
	}
}

int	built_in_path(char *cmd_new)
{
	int	len_path;

	len_path = ft_strlen(cmd_new);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("env")]), "env") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("export")]), "export") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("echo")]), "echo") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("cd")]), "cd") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("pwd")]), "pwd") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("unset")]), "unset") == 0)
		return (1);
	return (0);
}

int	ft_verify(char *cmd, char *path)
{
	if (ft_strlen(path) != ft_strlen(cmd))
	{
		if (ft_strchr(cmd, '/'))
			return (1);
	}
	return (0);
}

int	ft_bin_(t_master *master, char **av, char *path)
{
	char	*cmd_new;

	if (execve(av[0], av, master->environ) != 0)
	{
		if (ft_strchr(av[0], '/'))
			return (-1);
		cmd_new = malloc(ft_strlen(path) + ft_strlen(av[0]) + 2);
		if (built_in_path(cmd_new))
		{
			free(cmd_new);
			return (-1);
		}
		if (!cmd_new)
			return (-1);
		ft_strcpy(cmd_new, path);
		ft_strcat(cmd_new, ft_strstr(cmd_new, av[0]));
		if (execve(cmd_new, av, master->environ) != 0)
		{
			free(cmd_new);
			return (-1);
		}
	}
	free(cmd_new);
	return (0);
}

void	ft_bin(t_master *master, char **av)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	path = ft_getenv(master->environ, "PATH");
	paths = ft_split(path, ':');
	while (paths[i])
	{
		path = ft_very_and_bar(paths[i]);
		if (!path)
		{
			i++;
			continue ;
		}
		if (ft_bin_(master, av, path) != 0)
		{
			free(path);
			i++;
		}
	}
	free_matriz(paths);
	ft_current_dir(master, av);
}
