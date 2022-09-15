/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/13 16:59:13 by vsedat           ###   ########lyon.fr   */
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

int	checkinterlife(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->mbasetime);
	writeaction(get_time() - philo[i].data->basetime,
		philo[i].philoid, "died", philo);
	pthread_mutex_unlock(&philo[i].data->mbasetime);
	pthread_mutex_lock(&philo[i].data->meveryonealive);
	philo[i].data->everyonealive = 0;
	pthread_mutex_unlock(&philo[i].data->meveryonealive);
	pthread_mutex_unlock(&philo[i].data->mtimetodie);
	pthread_mutex_unlock(&philo[i].mlasteat);
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
		pthread_mutex_lock(&philos[i].data->mmaxeat);
		pthread_mutex_lock(&philos[i].mnbeaten);
		if (philos[i].nbeaten <= philos[i].data->maxeat
			|| philos->data->maxeat == -1)
		{
			pthread_mutex_unlock(&philos[i].data->mmaxeat);
			pthread_mutex_unlock(&philos[i].mnbeaten);
			pthread_mutex_unlock(&philos[i].data->mnbphilo);
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
	while (i < philos[0].data->nbphilo - 1)
	{
		pthread_mutex_lock(&philos[i].data->mtimetodie);
		pthread_mutex_lock(&philos[i].mlasteat);
		if (philos[i].lasteat + philos[i].data->timetodie < get_time())
		{
			checkinterlife(philos, i);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].data->mtimetodie);
		pthread_mutex_unlock(&philos[i].mlasteat);
		i++;
	}
	pthread_mutex_unlock(&philos[i].data->mnbphilo);
	return (checkmaxeat(philos));
}

void	willforkr(t_philo *philo, int basetime)
{
	pthread_mutex_lock(&philo->rfork);
	pthread_mutex_lock(&philo->data->mbasetime);
	writeaction(get_time() - basetime, philo->philoid,
		"fork", philo);
	pthread_mutex_unlock(&philo->data->mbasetime);
}

void	willforkl(t_philo *philo, int basetime)
{
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(&philo->data->mbasetime);
	writeaction(get_time() - basetime, philo->philoid,
		"fork", philo);
	pthread_mutex_unlock(&philo->data->mbasetime);
}

void	willeat(t_philo *philo, int basetime)
{
	pthread_mutex_lock(&philo->data->mbasetime);
	writeaction(get_time() - basetime, philo->philoid,
		"eating", philo);
	pthread_mutex_unlock(&philo->data->mbasetime);
	pthread_mutex_lock(&philo->mlasteat);
	philo->lasteat = get_time();............
	pthread_mutex_unlock(&philo->mlasteat);
	pthread_mutex_lock(&philo->mnbeaten);
	philo->nbeaten++;
	pthread_mutex_unlock(&philo->mnbeaten);
	ft_msleep(philo->data->timetoeat);
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	willsleep(t_philo *philo, int basetime)
{
	pthread_mutex_lock(&philo->data->mbasetime);
	writeaction(get_time() - basetime, philo->philoid,
		"sleeping", philo);
	pthread_mutex_unlock(&philo->data->mbasetime);
	ft_msleep(philo->data->timetosleep);
}

int	myphilonext(t_philo *philo, int basetime)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->meveryonealive);
		if (!philo->data->everyonealive)
		{
			pthread_mutex_unlock(&philo->data->meveryonealive);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meveryonealive);
		writeaction(get_time() - basetime, philo->philoid,
			"thinking", philo);
		willforkl(philo, basetime);
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
	if (philo->philoid % 2 == 0)
		usleep(100);
//	pthread_mutex_lock(&philo->data->mnbphilo);
//	if (philo->data->nbphilo == 1)
//	{
//		pthread_mutex_unlock(&philo->data->mnbphilo);
//		return (0);
//	}
//	pthread_mutex_unlock(&philo->data->mnbphilo);
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
	usleep(10000);
	while (1)
		if (!checklife(philos))
			break ;
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(thread_id[i], NULL);
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
