/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:17:51 by vsedat            #+#    #+#             */
/*   Updated: 2022/09/19 13:17:53 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

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
	philo->lasteat = get_time();
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
