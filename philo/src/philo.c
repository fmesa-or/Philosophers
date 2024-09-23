/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oceanscore <oceanscore@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:41 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/22 18:10:39 by oceanscore       ###   ########.fr       */
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
		return (-1);
	}
	if (create_table(av, &table) == -1)
		return (-1);
	if (create_philo(&table, &philo) == -1)
		return (-1);
	if (table->n_philos == 1)
		return (ft_diner_4_1(&philo));
	if (create_threads(&table, &philo) == -1)
		return (-1);
	if (join_threads(&philo) == -1)
		return (-1);
	return (0);
}