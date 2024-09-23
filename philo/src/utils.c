/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:37:42 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/23 20:34:20 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isundigit(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str > '9' || *str < '0')
			return (-1);
		str++;
	}
	return (0);
}

int	check_parse(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return(-1);
	else
	{
		while (++i < ac)
		{
			if ((ft_isundigit(av[i])) == -1)
				return(-1);
		}
	}
	return(0);
}


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
	if (ft_graveyard(philo))
		return (-1);
	while ((ft_get_time() - (*philo).t_meals) < (*philo).table->t_die)
	{
		if (ft_graveyard(philo))
			return (-1);
		pthread_mutex_lock(&(*philo).table->print);
		if ((*philo).table->dead == true)
			return (-1);
		pthread_mutex_unlock(&(*philo).table->print);
		if ((ft_get_time() - t_start) >= time)
			return (0);
		usleep(10000);
	}
	pthread_mutex_lock(&(*philo).table->print);
	(*philo).table->dead = true;
	printf(RD"[%lu] %lu died\n"RES, (ft_get_time() - philo->table->start_time), philo->id);
	pthread_mutex_unlock(&(*philo).table->print);
//	pthread_mutex_unlock(philo->r_fork);
//	pthread_mutex_unlock(philo->l_fork);
	return (-1);
}

/*
*1st:	Checks if someone is dead.
*2nd:	Saves the time when function is called.
*3rd:	Prints the message.
*4th:	*/
int	eating(t_philo *philo)
{
	if (ft_graveyard(philo))
		return (-1);
	pthread_mutex_lock(&(*philo).table->print);
	printf(GR"[%lu] %lu is eating\n"RES, (ft_get_time() - philo->table->start_time), (*philo).id);
	(*philo).meals++;
	pthread_mutex_unlock(&(*philo).table->print);
	if (uwait(&(*philo), (*philo).table->t_eat) == -1)
		return (-1);
	return (0);
}
