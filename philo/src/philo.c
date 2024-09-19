/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:41 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/19 19:11:14 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*table;
	t_philo	*philo;

	if (check_parse(ac, av) == -1)
	{
		printf(RD"Error:\tWrong input.\n"PR"Ex:\t./philo " \
		"(philosophers) (time_to_die) (eat_time) (sleep_time) " \
		"[target_meals]\n"RES);
		return(-1);
	}
//	table = (t_table *)malloc(sizeof(t_table *));
	if (create_table(av, &table) == -1)
		return (-1);
	if (create_philo(av, &table, &philo) == -1)
		return (-1);
	if (create_threads(&table, &philo) == -1)
		return (-1);
	join_threads();
	return (0);
}