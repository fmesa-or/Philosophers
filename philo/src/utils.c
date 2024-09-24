/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:37:42 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/24 20:36:55 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




/**********************************************
*Returns the exact time in miliseconds.       *
*tv_sec stores second at the moment           *
*tv_usec stores the microseconds at the moment*
**********************************************/
unsigned long	ft_get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
*time	= amount of time necesary to complette the task.*
*Waits the amount of time to complette the task while checking if someone died.*
*Remember:	The spawn of life time is mesured with the last time the philosopher eated.*
*/
int	uwait(t_philo *philo, unsigned long time)
{
	unsigned long	t_start;

	t_start = ft_get_time();
	if (ft_graveyard(philo) == -1)
		return (-1);
	while ((ft_get_time() - (*philo).t_meals) < (*philo).table->t_die)
	{
		if (ft_graveyard(philo) == -1)
			return (-1);
		if ((ft_get_time() - t_start) >= time)
			return (0);
		usleep(10000);
	}
	pthread_mutex_lock(&philo->table->reaper);
	if (philo->table->dead == true)
	{
		pthread_mutex_unlock(&philo->table->reaper);
		return (-1);
	}
	philo->table->dead = true;
	if (printer_dead(philo) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->table->reaper);
	return (-1);
}

/*
*1st:	Checks if someone is dead.
*2nd:	Saves the time when function is called.
*3rd:	Prints the message.
*4th:	*/
int	eating(t_philo *philo)
{
	if (ft_graveyard(philo) == -1)
	{
		return (-1);
	}
	if (printer(philo, 'E') == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->reaper);
	if (philo->meals == philo->table->meals)
		philo->table->sated++;
	if (philo->table->sated == philo->table->n_philos)
	{
		philo->table->dead = true;
		pthread_mutex_unlock(&philo->table->reaper);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->reaper);
	if (uwait(&(*philo), (*philo).table->t_eat) == -1)
		return (-1);
	return (0);
}
