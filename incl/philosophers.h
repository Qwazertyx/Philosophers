/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:37:46 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/01 13:00:51 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include	<stdio.h>
# include	<unistd.h>

typedef struct s_data
{
	int	nbphilo;
	int	timetodie;
	int	timetoeat;
	int	timetosleep;
	int	maxeat;
}					t_data;

int		parsing(int argc, char *argv[]);
int		ft_atoi(char *str);
void	fillstruct(char *argv[], t_data *data);
void	writeaction(int timestamp, int nbphilo, char *action);
int		ft_strcmp(char *s1, char *s2);

#endif
