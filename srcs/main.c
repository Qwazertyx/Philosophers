/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/21 18:22:34 by vsedat           ###   ########lyon.fr   */
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

void	unlockfork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

int	checkphilos(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < philos[i]->data.nbphilo)
	{
		if (!philos[i]->data.everyonealive)
			return (0);
	}
	return (0);
}

int	checklife(t_philo	*philo, int basetime)
{
	printf("a||\n");
	if (philo->lasteat - basetime > philo->data.timetodie)
	{
		writeaction(get_time() - philo->basetime, philo->philoid, "died");
		philo->data.everyonealive = 0;
		printf("dd\n");
		return (0);
	}
	printf("sdd\n");
	return (1);
}

void	forkeatsleep(t_philo *philo, int basetime)
{
	pthread_mutex_lock(&philo->rfork);
	writeaction(get_time() - basetime, philo->philoid, "fork");
	pthread_mutex_lock(philo->lfork);
	writeaction(get_time() - basetime, philo->philoid, "fork");
	philo->lasteat = get_time();
	philo->nbeaten++;
	writeaction(get_time() - basetime, philo->philoid, "eating");
	ft_msleep(philo->data.timetoeat);
	unlockfork(philo);
	writeaction(get_time() - basetime, philo->philoid, "sleeping");
	ft_msleep(philo->data.timetosleep);
}

void	myphilonext(t_philo *philo, int basetime)
{
	while (philo->data.everyonealive == 1)
	{
		printf("s||\n");
		writeaction(get_time() - basetime, philo->philoid, "thinking");
		forkeatsleep(philo, basetime);
	}
}

void	*myphilofun(void *philos)
{
	t_philo	*philo;
	int		basetime;

	basetime = get_time();
	philo->basetime = get_time();
	philo = (t_philo *)philos;
	if (philo->data.nbphilo % 2 == 0)
	{
		if (philo->philoid % 2 != 0)
			forkeatsleep(philo, basetime);
		else
			usleep(100);
		myphilonext(philo, basetime);
	}
	else
	{
		if (philo->philoid % 2 == 0)
			forkeatsleep(philo, basetime);
		else
			usleep(100);
		myphilonext(philo, basetime);
	}
	return (0);
}


int	main(int argc, char *argv[])
{
	pthread_t		*thread_id;
	t_philo			*philos;
	int				i;

	if (!parsing(argc, argv))
		return (0 * printf("Error\n"));
	philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	thread_id = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	fillmyphilos(argv, philos);
	i = -1;
	printf("||d\n");
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].philoid = i + 1;
		pthread_create(&thread_id[i], NULL, myphilofun, &philos[i]);
	}
	printf("dd||\n");
	while (1)
		if (!checkphilos(&philos))
			return (0);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(thread_id[i], NULL);
	i = 0;
	freephils(thread_id, philos);
	return (0);
}
