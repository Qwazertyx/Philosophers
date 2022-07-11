/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:01:57 by vsedat            #+#    #+#             */
/*   Updated: 2022/07/01 13:11:46 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	printf("%d\n", argc);
	if (!parsing(argc, argv))
		return (0);
	fillstruct(argv, &data);

	printf("%d\n", data.nbphilo);
	printf("%d\n", data.timetodie);
	printf("%d\n", data.timetoeat);
	printf("%d\n", data.timetosleep);
	printf("%d\n", data.maxeat);
	return(0);
}
