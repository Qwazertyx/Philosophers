/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/19 13:18:21 by vsedat           ###   ########lyon.fr   */
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
		writeaction(get_time() - basetime, philo->philoid,
			"thinking", philo);
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

int	philo(char *argv[])
{
	pthread_t	*thread_id;
	t_philo		*philos;
	int			i;

	philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	thread_id = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	fillmyphilos(argv, philos);
	i = -1;
	pthread_mutex_lock(&philos[0].data->start);
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].philoid = i + 1;
		pthread_create(&thread_id[i], NULL, myphilofun, &philos[i]);
	}
	philos[0].data->basetime = get_time();
	pthread_mutex_unlock(&philos[0].data->start);
	usleep(3000);
	while (1)
		if (!checklife(philos))
			break ;
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(thread_id[i], NULL);
	usleep(10000);
	freephils(thread_id, philos);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (!parsing(argc, argv))
		return (0);
	philo(argv);
	return (0);
}
