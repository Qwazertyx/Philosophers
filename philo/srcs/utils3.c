/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:15:37 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/19 13:15:45 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

void	ft_msleep(int ms)
{
	int	time;
	int	i;

	time = get_time();
	i = time;
	while (i < time + ms)
	{
		i = get_time();
		usleep(100);
	}
}
