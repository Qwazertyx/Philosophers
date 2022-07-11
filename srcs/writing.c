/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:54 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/01 13:00:40 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

void	writeaction(int timestamp, int nbphilo, char *action)
{
	if (!ft_strcmp(action, "fork"))
		printf("%d %d has taken a fork\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "eating"))
		printf("%d %d is eating\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "sleeping"))
		printf("%d %d is sleeping\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "thinking"))
		printf("%d %d is thinking\n", timestamp, nbphilo);
	if (!ft_strcmp(action, "died"))
		printf("%d %d died\n", timestamp, nbphilo);
}
