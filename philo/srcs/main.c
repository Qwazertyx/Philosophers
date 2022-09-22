/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/21 14:07:51 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	myonlyphilo(t_philo *philo, int basetime)
{
	int	t;

	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_lock(&philo->data->mbasetime);
	pthread_mutex_lock(&philo->data->mtimetodie);
	pthread_mutex_unlock(&philo->data->mbasetime);
	t = philo->data->timetodie;
	pthread_mutex_unlock(&philo->data->mtimetodie);
	ft_msleep(t);
	writeaction(get_time() - basetime, philo->philoid,
		"died", philo);
}

int	myphilonext(t_philo *philo, int basetime)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->meveryonealive);
		if (!philo->data->everyonealive)
			return (0 * pthread_mutex_unlock(&philo->data->meveryonealive));
		pthread_mutex_unlock(&philo->data->meveryonealive);
		willforkl(philo, basetime);
		pthread_mutex_lock(&philo->data->mnbphilo);
		if (philo->data->nbphilo == 1)
		{
			pthread_mutex_unlock(&philo->data->mnbphilo);
			myonlyphilo(philo, basetime);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->mnbphilo);
		willforkr(philo, basetime);
		willeat(philo, basetime);
		willsleep(philo, basetime);
		writeaction(get_time() - basetime, philo->philoid,
			"thinking", philo);
	}
	return (0);
}

void	*myphilofun(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	pthread_mutex_lock(&philo->mlasteat);
	philo->lasteat = get_time();
	pthread_mutex_unlock(&philo->mlasteat);
	if (philo->philoid % 2)
		usleep(2000);
	myphilonext(philo, philo->data->basetime);
	return (0);
}

int	philo(char *argv[], pthread_t *thread_id, t_philo *philos)
{
	int	i;

	if (!fillmyphilos(argv, philos))
	{
		free(philos);
		free(thread_id);
		free(philos->data);
		return (0);
	}
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].philoid = i + 1;
		pthread_create(&thread_id[i], NULL, myphilofun, &philos[i]);
	}
	philos[0].data->basetime = get_time();
	pthread_mutex_unlock(&philos[0].data->start);
	usleep(5000);
	while (checklife(philos))
		usleep(10);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(thread_id[i], NULL);
	usleep(10000);
	return (freephils(thread_id, philos));
}

int	main(int argc, char *argv[])
{
	pthread_t	*thread_id;
	t_philo		*philos;

	if (!parsing(argc, argv))
		return (0);
	philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (!philos)
	{
		free(philos);
		return (0);
	}
	thread_id = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	if (!thread_id)
	{
		free(philos);
		free(thread_id);
		return (0);
	}
	philo(argv, thread_id, philos);
	return (1);
}
