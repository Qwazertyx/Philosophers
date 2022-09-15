/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:37:46 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/12 14:01:58 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_data
{
	int				nbphilo;
	pthread_mutex_t	mnbphilo;
	int64_t			basetime;
	pthread_mutex_t	mbasetime;
	int				timetodie;
	pthread_mutex_t	mtimetodie;
	int				timetoeat;
	int				timetosleep;
	int				maxeat;
	pthread_mutex_t	mmaxeat;
	int				everyonealive;
	pthread_mutex_t	meveryonealive;
	pthread_mutex_t	start;
}					t_data;

typedef struct s_philo
{
	int				philoid;
	int64_t			lasteat;
	pthread_mutex_t	mlasteat;
	int				nbeaten;
	pthread_mutex_t	mnbeaten;
	pthread_mutex_t	rfork;
	pthread_mutex_t	*lfork;
	t_data			*data;
}					t_philo;

int64_t	get_time(void);
int		parsing(int argc, char *argv[]);
int		ft_atoi(char *str);
void	fillmyphilos(char *argv[], t_philo *philos);
void	writeaction(int timestamp, int nbphilo, char *action, t_philo *philo);
int		ft_strcmp(char *s1, char *s2);
int		freephils(pthread_t *t, t_philo *p);
#endif