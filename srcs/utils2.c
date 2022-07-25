/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:54 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/23 13:12:33 by vsedat           ###   ########lyon.fr   */
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

//philo 0 rfork: 0
//philo 1 rfork: 1
//philo 1 lfork: 0
//philo 2 rfork: 2
//philo 2 lfork: 1
//philo 3 rfork: 3
//philo 3 lfork: 2
//philo 4 rfork: 4
//philo 4 lfork: 3
//philo 0 lfork: 4

void	fillmyphilos(char *argv[], t_philo *philos)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&philos[i].rfork, NULL);
		philos[i].lasteat = 0;
		philos[i].nbeaten = 0;
		philos[i].data.basetime = get_time();
		philos[i].data.nbphilo = ft_atoi(argv[1]);
		philos[i].data.timetodie = ft_atoi(argv[2]);
		philos[i].data.timetoeat = ft_atoi(argv[3]);
		philos[i].data.timetosleep = ft_atoi(argv[4]);
		philos[i].data.maxeat = -1;
		if (argv[5])
			philos[i].data.maxeat = ft_atoi(argv[5]);
		philos[i].data.everyonealive = 1;
		i++;
	}
	i = 1;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].lfork = &philos[i - 1].rfork;
		i++;
	}
	philos[0].lfork = &philos[i - 1].rfork;
}

int	freephils(pthread_t *thread_id, t_philo *philos)
{
	free(thread_id);
	free(philos);
	return (0);
}

void	writeaction(int timestamp, int nbphilo, char *action)
{
	if (!ft_strcmp(action, "eating"))
		printf("%d %d is eating\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "sleeping"))
		printf("%d %d is sleeping\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "thinking"))
		printf("%d %d is thinking\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "died"))
		printf("%d %d died\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "fork"))
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "rfork"))
		printf("%d %d has taken a rfork\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "lfork"))
		printf("%d %d has taken a lfork\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "forks"))
	{
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
	}
}
