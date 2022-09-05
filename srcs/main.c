/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/05 12:11:34 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int64_t	get_time(void)
{
	static struct timeval tv;

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

void	unlockfork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

int	checkphilos(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < philos[i]->data->nbphilo)
	{
		if (!philos[i]->data->everyonealive)
			return (0);
	}
	return (0);
}

int	checklife(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->nbphilo - 1)
	{
		pthread_mutex_lock(&philo->mlasteat);
		if (philo[i].lasteat + (int64_t)philo[i].data->timetodie < get_time())
		{
			writeaction(get_time() - philo[i].data->basetime,
						philo[i].philoid, "died");
			pthread_mutex_lock(&philo[0].data->meveryonealive);
			philo[i].data->everyonealive = 0;
			pthread_mutex_unlock(&philo[0].data->meveryonealive);
			return (0);
		}
		pthread_mutex_unlock(&philo->mlasteat);
		i++;
	}

	return (1);
}

void	willforkr(t_philo *philo, int basetime)
{
	pthread_mutex_lock(&philo->rfork);
	writeaction(get_time() - basetime, philo->philoid, "fork");
}

void	willforkl(t_philo *philo, int basetime)
{
	pthread_mutex_lock(philo->lfork);
	writeaction(get_time() - basetime, philo->philoid, "fork");
}

void	willeat(t_philo *philo, int basetime)
{
	writeaction(get_time() - basetime, philo->philoid, "eating");
	pthread_mutex_lock(&philo->mlasteat);
	philo->lasteat = get_time();
	// dprintf(2, "%d %lld\n", philo->philoid, get_time());
	// dprintf(2, "%d %lld\n", philo->philoid, philo->lasteat + philo->data->timetodie);
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
	writeaction(get_time() - basetime, philo->philoid, "sleeping");
	ft_msleep(philo->data->timetosleep);
}

// void	forkeatsleep(t_philo *philo, int basetime)
//{
//	pthread_mutex_lock(&philo->rfork);
//	writeaction(get_time() - basetime, philo->philoid, "fork");
//	pthread_mutex_lock(philo->lfork);
//	writeaction(get_time() - basetime, philo->philoid, "fork");
//	writeaction(get_time() - basetime, philo->philoid, "eating");
//	philo->lasteat = get_time();
//	philo->nbeaten++;
//	ft_msleep(philo->data->timetoeat);
//	unlockfork(philo);
//	writeaction(get_time() - basetime, philo->philoid, "sleeping");
//	ft_msleep(philo->data->timetosleep);
// }

int	myphilonext(t_philo *philo, int basetime)
{
	while (1)
	{
		pthread_mutex_lock(&philo[0].data->meveryonealive);
		if (!philo->data->everyonealive)
			return (0);
		pthread_mutex_unlock(&philo[0].data->meveryonealive);
		writeaction(get_time() - basetime, philo->philoid, "thinking");
		willforkl(philo, basetime);
		willforkr(philo, basetime);
		willeat(philo, basetime);
		willsleep(philo, basetime);
		//	forkeatsleep(philo, basetime);
	}
	return (0);
}

void	*myphilofun(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	philo->lasteat = get_time();
	if (philo->philoid % 2 == 0)
		usleep(100);
	myphilonext(philo, philo->data->basetime);
	// if (philo->data->nbphilo % 2 != 0)
	// {
	// 	if (philo->philoid % 2 != 0)
	// 		myphilonext(philo, philo->data->basetime);
	// 	else
	// 		usleep(100);
	// 	myphilonext(philo, philo->data->basetime);
	// }
	// else
	// {
	// 	if (philo->philoid % 2 == 0)
	// 		myphilonext(philo, philo->data->basetime);
	// 	else
	// 		usleep(100);
	// 	myphilonext(philo, philo->data->basetime);
	// }
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
	usleep(200);
	while (1)
		if (!checklife(philos))
			return (freephils(thread_id, philos));
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(thread_id[i], NULL);
	freephils(thread_id, philos);
}

int	main(int argc, char *argv[])
{
	if (!parsing(argc, argv))
		return (0);
	philo(argv);
	return (0);
}
