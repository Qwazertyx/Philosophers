/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:54 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/21 13:56:23 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

void	initmutex(char *argv[], t_data *data)
{
	data->nbphilo = ft_atoi(argv[1]);
	data->timetodie = ft_atoi(argv[2]);
	data->timetoeat = ft_atoi(argv[3]);
	data->timetosleep = ft_atoi(argv[4]);
	data->maxeat = -1;
	if (argv[5])
		data->maxeat = ft_atoi(argv[5]);
	data->everyonealive = 1;
	pthread_mutex_init(&data->meveryonealive, NULL);
	pthread_mutex_init(&data->mtimetodie, NULL);
	pthread_mutex_init(&data->mbasetime, NULL);
	pthread_mutex_init(&data->mnbphilo, NULL);
	pthread_mutex_init(&data->mmaxeat, NULL);
	pthread_mutex_init(&data->start, NULL);
}

int	fillmyphilos(char *argv[], t_philo *philos)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	pthread_mutex_init(&data->start, NULL);
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&philos[i].rfork, NULL);
		pthread_mutex_init(&philos[i].mlasteat, NULL);
		pthread_mutex_init(&philos[i].mnbeaten, NULL);
		philos[i].nbeaten = 0;
		philos[i].lasteat = 0;
		philos[i].data = data;
		i++;
	}
	initmutex(argv, data);
	i = 0;
	while (++i < ft_atoi(argv[1]))
		philos[i].lfork = &philos[i - 1].rfork;
	philos[0].lfork = &philos[i - 1].rfork;
	pthread_mutex_lock(&philos[0].data->start);
	return (1);
}

int	freephils(pthread_t *thread_id, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nbphilo)
	{
		pthread_mutex_destroy(&philos[i].rfork);
		pthread_mutex_destroy(&philos[i].mnbeaten);
		pthread_mutex_destroy(&philos[i].mlasteat);
		i++;
	}
	pthread_mutex_destroy(&philos[0].data->mnbphilo);
	pthread_mutex_destroy(&philos[0].data->mbasetime);
	pthread_mutex_destroy(&philos[0].data->mtimetodie);
	pthread_mutex_destroy(&philos[0].data->meveryonealive);
	pthread_mutex_destroy(&philos[0].data->start);
	free(philos[0].data);
	free(thread_id);
	free(philos);
	return (0);
}

void	writeaction(int timestamp, int nbphilo, char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meveryonealive);
	if (!philo->data->everyonealive)
		;
	else if (!ft_strcmp(action, "eating"))
		printf("%d %d is eating\n", timestamp, nbphilo);
	else if (!ft_strcmp(action, "sleeping"))
		printf("%d %d is sleeping\n", timestamp, nbphilo);
	else if (!ft_strcmp(action, "thinking"))
		printf("%d %d is thinking\n", timestamp, nbphilo);
	else if (!ft_strcmp(action, "fork"))
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
	else if (!ft_strcmp(action, "rfork"))
		printf("%d %d has taken a rfork\n", timestamp, nbphilo);
	else if (!ft_strcmp(action, "lfork"))
		printf("%d %d has taken a lfork\n", timestamp, nbphilo);
	else if (!ft_strcmp(action, "forks"))
	{
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
	}
	if (!ft_strcmp(action, "died"))
		printf("%d %d died\n", timestamp, nbphilo);
	pthread_mutex_unlock(&philo->data->meveryonealive);
}
