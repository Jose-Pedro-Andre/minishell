/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:49 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/29 15:06:37 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_matriz(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL || (*mat) == NULL)
		return (0);
	while (mat[i] != NULL)
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**tmp;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	tmp = (char **)malloc((ft_count_matriz(arr) + 1) * sizeof(char *));
	i = 0;
	while (arr[i] != NULL)
	{
		tmp[i] = ft_strdup(arr[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_matriz(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL || *mat == NULL)
	{
		free(mat);
		return ;
	}
	while (mat[i])
		free(mat[i++]);
	free(mat);
}