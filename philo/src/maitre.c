/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maitre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:08:43 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/25 13:49:09 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**************************************************************************
*1st:	Assigns all the data.                                             *
*2nd:	Saves space for the forks and initializes all of them.            *
*3rd:	Starts the mutex for the print mutex.                             *
*4th:	If there is a number of meals to eat, it will store the data also.*
*5th:	Saves the start time of the program.                              *
**************************************************************************/
int	create_table(char **av, t_table *table)
{
	unsigned long	i;

	table->dead = false;
	table->n_philos = (ft_atoul(av[1]));
	table->t_die = (ft_atoul(av[2]));
	table->t_eat = (ft_atoul(av[3]));
	table->t_sleep = (ft_atoul(av[4]));
	table->sated = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!(table->forks))
		return (-1);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print, NULL);
	if (av[5])
		table->meals = ft_atoul(av[5]);
	else
		table->meals = -1;
	table->start_time = ft_get_time();
	return (0);
}

/*********************************************************
*Asigns all the data for every philosopher.              *
*		The last time each one eaten it's the start time.*
*********************************************************/
int	create_philo(t_table *table, t_philo *philo)
{
	unsigned long	i;

	i = 0;
	while (i < (table->n_philos))
	{
		philo[i].id = (i + 1);
		philo[i].table = table;
		philo[i].r_fork = &table->forks[i];
		philo[i].l_fork = &table->forks[(i + 1) % table->n_philos];
		philo[i].meals = 0;
		philo[i].t_meals = table->start_time;
		i++;
	}
	return (0);
}