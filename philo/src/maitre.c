/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maitre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oceanscore <oceanscore@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:08:43 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/22 17:43:49 by oceanscore       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**************************************************************************
*1st:	Saves space for the table, and asigns all the data.               *
*2nd:	Saves space for the forks and asigns all of them.                 *
*3rd:	Starts the mutex for the print mutex.                             *
*4th:	If there is a number of meals to eat, it will store the data also.*
**************************************************************************/
int	create_table(char **av, t_table **table)
{
	unsigned long	i;

	*table = malloc(sizeof(t_table));
	if (!*table)
		return (-1);
	(*table)->dead = false;
	(*table)->n_philos = (ft_atoul(av[1]));
	(*table)->t_die = (ft_atoul(av[2]));
	(*table)->t_eat = (ft_atoul(av[3]));
	(*table)->t_sleep = (ft_atoul(av[4]));
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * (*table)->n_philos);
	i = 0;
	while (i < (*table)->n_philos)
	{
		pthread_mutex_init((&(*table)->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(*table)->print, NULL);
	if (av[5])
		(*table)->meals = ft_atoul(av[5]);
	else
		(*table)->meals = -1;
	(*table)->start_time = ft_get_time();
	return (0);
}

/***************************************************************
*1st:	Saves space for all the philosophers (inside an array).*
*2nd:	Asigns all the data for every philosopher.             *
***************************************************************/
int	create_philo(t_table **table, t_philo **philo)
{
	unsigned long	i;

	(*philo) = malloc(sizeof(t_philo *) * (*table)->n_philos);
	if (!philo)
		return (-1);
	i = 0;
	while (i < ((*table)->n_philos))
	{
		(*philo)[i].id = (i + 1);
		(*philo)[i].table = *table;
		(*philo)[i].r_fork = (*table)->forks[i];
		(*philo)[i].l_fork = (*table)->forks[(i + 1) % (*table)->n_philos];
		(*philo)[i].meals = 0;
		(*philo)[i].t_meals = (*table)->start_time;
		i++;
	}
	return (0);
}