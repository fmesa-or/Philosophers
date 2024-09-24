/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:41 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/24 19:34:02 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*table;
	t_philo	*philo;

	if (check_parse(ac, av) == -1)
		return (-1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (-1);
	if (create_table(av, table) == -1)
		return (-1);
	if (ft_n_meals(table) == -1)
		return (-1);
	philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!philo)
		return (-1);
	if (create_philo(table, philo) == -1)
		return (-1);
	if (table->n_philos == 1)
		return (ft_diner_4_1(philo, table));
	if (create_threads(table, philo) == -1)
		return (-1);
	if (join_threads(philo) == -1)
		return (-1);
	free(table);
	free(philo);
	return (0);
}
