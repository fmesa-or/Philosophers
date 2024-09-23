/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:42:26 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/23 19:20:39 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int	create_threads(t_table *table, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	if (!philo)
		return (-1);
	while (i < table->n_philos)
	{
		if ((pthread_create(&philo[i].thread, NULL, (void *) &ft_routine, (void *) &philo[i])) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_threads(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < (philo)->table->n_philos)
	{
		if ((pthread_join(philo[i].thread, NULL)) != 0)
			return (-1);
		i++;
	}
	return (0);
}
