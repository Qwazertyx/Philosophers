/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:39:15 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/01 13:11:55 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

int	toosmbig(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > 2147483647)
			return (0);
		if (ft_atoi(argv[i]) < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

int	parsing(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	if (!toosmbig(argv))
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!isnumber(argv[i]) || (argv[i][0] == '-' && !argv[i][1]))
			return (0);
		if (argv[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}
