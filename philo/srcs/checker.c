/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:16:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/21 14:00:59 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	checkinterlife(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->mbasetime);
	writeaction(get_time() - philo[i].data->basetime,
		philo[i].philoid, "died", philo);
	pthread_mutex_unlock(&philo[i].data->mbasetime);
	pthread_mutex_lock(&philo[i].data->meveryonealive);
	philo[i].data->everyonealive = 0;
	pthread_mutex_unlock(&philo[i].data->meveryonealive);
	pthread_mutex_unlock(&philo[i].data->mnbphilo);
	return (0);
}

int	checkmaxeat(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos[i].data->mnbphilo);
	while (i < philos[0].data->nbphilo - 1)
	{
		pthread_mutex_unlock(&philos[0].data->mnbphilo);
		pthread_mutex_lock(&philos[i].data->mmaxeat);
		pthread_mutex_lock(&philos[i].mnbeaten);
		if (philos[i].nbeaten <= philos[i].data->maxeat
			|| philos->data->maxeat == -1)
		{
			pthread_mutex_unlock(&philos[i].data->mmaxeat);
			pthread_mutex_unlock(&philos[i].mnbeaten);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].data->mmaxeat);
		pthread_mutex_unlock(&philos[i].mnbeaten);
		i++;
	}
	pthread_mutex_lock(&philos[i].data->meveryonealive);
	philos[i].data->everyonealive = 0;
	pthread_mutex_unlock(&philos[i].data->meveryonealive);
	pthread_mutex_unlock(&philos[i].data->mnbphilo);
	return (0);
}

int	checklife(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos[i].data->mnbphilo);
	while (i < philos[0].data->nbphilo)
	{
		pthread_mutex_unlock(&philos[0].data->mnbphilo);
		pthread_mutex_lock(&philos[i].data->mtimetodie);
		pthread_mutex_lock(&philos[i].mlasteat);
		if (philos[i].lasteat && philos[i].lasteat
			+ philos[i].data->timetodie < get_time())
		{
			pthread_mutex_unlock(&philos[i].data->mtimetodie);
			pthread_mutex_unlock(&philos[i].mlasteat);
			checkinterlife(philos, i);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].data->mtimetodie);
		pthread_mutex_unlock(&philos[i].mlasteat);
		i++;
	}
	pthread_mutex_unlock(&philos[0].data->mnbphilo);
	return (checkmaxeat(philos));
}
