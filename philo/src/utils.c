/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:37:42 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/27 12:07:30 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**********************************************
*Returns the exact time in miliseconds.       *
*tv_sec stores second at the moment           *
*tv_usec stores the microseconds at the moment*
**********************************************/
unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*******************************************************
*Changes the argument input to an unsigned long number.*
*******************************************************/
unsigned long	ft_atoul(const char *str)
{
	long			i;
	unsigned long	n;

	i = 0;
	n = 0;
	while (str[i] >= 9 && str[i] <= 13)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n += str[i] - 48;
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			n *= 10;
		i++;
	}
	return (n);
}

/***********************************************************
*This special function only works for just one philosopher,*
* so we don't waste resources.                             *
***********************************************************/
int	ft_diner_for_one(t_philo *philo, t_table *table)
{
	printf(CI"[%lu] %lu has taken a fork\n"RES,
		(ft_get_time() - philo->table->start_time), philo->id);
	usleep(philo->table->t_die * 1000);
	printf(RD"[%lu] %lu died\n"RES,
		(ft_get_time() - philo->table->start_time), philo->id);
	free(table->forks);
	free(table);
	free(philo);
	return (-1);
}

/*************************************************************
*Checks if someone is dead and if the philosopher has to die.*
*************************************************************/
int	ft_graveyard(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->reaper);
	pthread_mutex_lock(&philo->table->print);
	if ((ft_get_time() - (*philo).t_meals) > (*philo).table->t_die
		&& philo->table->dead == false)
	{
		philo->table->dead = true;
		printf(RD"[%lu] %lu died\n"RES,
			(ft_get_time() - philo->table->start_time), philo->id);
	}
	pthread_mutex_unlock(&philo->table->print);
	if (philo->table->dead == true)
	{
		pthread_mutex_unlock(&philo->table->reaper);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->reaper);
	return (0);
}
