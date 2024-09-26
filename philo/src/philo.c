/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:33:41 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/26 20:47:56 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo)
{
	unsigned long	i;

	i = 0;
	while (i < philo->table->n_philos)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->table->print);
	pthread_mutex_destroy(&philo->table->reaper);
	free(philo->table->forks);
	free(philo->table);
	free(philo);
}

int	main2(t_table *table, t_philo *philo)
{
	create_philo(table, philo);
	if (table->n_philos == 1)
		return (ft_diner_4_1(philo, table));
	if (create_threads(table, philo) == -1)
	{
		ft_free(philo);
		return (-1);
	}
	if (join_threads(philo) == -1)
	{
		ft_free(philo);
		return (-1);
	}
	return (0);
}

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
	{
		free(table);
		return (-1);
	}
	philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!philo)
	{
		free(table->forks);
		free(table);
		return (-1);
	}
	if (main2(table, philo) == -1)
		return (-1);
	ft_free(philo);
	return (0);
}
