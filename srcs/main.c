/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/20 16:54:12 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

void	*myphilofun(void *philos)
{
	t_philo	philofun;
	int		time;

	time = gettimeofday(0, 0);
	philofun = *(t_philo *)philos;
	if (philofun.philoid % 2 == 0)
	{
		writeaction(0, philofun.philoid, "fork");
		writeaction(0, philofun.philoid, "eating");
		philofun.lasteat = gettimeofday(0, 0);
	}
	else
		writeaction(gettimeofday(0, 0), philofun.philoid, "thinking");
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t		*thread_id;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;

	if (!parsing(argc, argv))
		return (0 * printf("Error\n"));
	philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	forks = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	thread_id = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	fillmyphilos(argv, philos);
	i = 0;
	while (i++ < ft_atoi(argv[1]))
	{
		philos[i].philoid = i;
		pthread_create(&thread_id[i], NULL, myphilofun, &philos[i]);
	}
	i = 0;
	while (i++ < ft_atoi(argv[1]))
		pthread_join(thread_id[i], NULL);
	freephils(thread_id, philos, forks);
	return (0);
}
