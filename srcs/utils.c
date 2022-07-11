/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:52:21 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/01 13:12:54 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	atoiparsing(char *str)
{
	int	i;

	i = 0;
	while ((((((str[i] == '\f' || str[i] == '\r')
						|| str[i] == ' ')
					|| str[i] == '\t')
				|| str[i] == '\n')
			|| str[i] == '\v') && str[i])
		i++;
	while (((str[i] == '+')
			|| str[i] == '-') && str[i])
		i++;
	return (i);
}

int	isnegatif(char *str)
{
	int	i;
	int	negatif;

	i = 0;
	negatif = 0;
	while ((str[i] < '0' || str[i] > '9'))
	{
		if (str[i] == '-')
			negatif++;
		i++;
	}
	if (negatif % 2 == 1)
		return (-1);
	return (1);
}

int	ft_atoi(char *str)
{
	int			i;
	int long	result;

	i = atoiparsing(str);
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (isnegatif(str) == -1)
		result *= -1;
	return (result);
}

void	fillstruct(char *argv[], t_data *data)
{
	int	i;

	i = 1;
	data->nbphilo = ft_atoi(argv[i]);
	data->timetodie = ft_atoi(argv[i + 1]);
	data->timetoeat = ft_atoi(argv[i + 2]);
	data->timetosleep = ft_atoi(argv[i + 3]);
	data->maxeat = -1;
	if (argv[i + 4])
		data->maxeat = ft_atoi(argv[i + 4]);
}
