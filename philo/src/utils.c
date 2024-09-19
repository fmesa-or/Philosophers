/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:37:42 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/19 20:18:50 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
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
			if ((ft_isdigit(av[i])) == -1)
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

int	uwait(t_philo *philo, unsigned long time)
{
	unsigned long	t_start;

	t_start = ft_get_time();
	while ((ft_get_time() - (*philo).t_meals) < (*philo).table->t_die)
	{
		
		pthread_mutex_lock(&(*philo).table->print);
		if ((*philo).table->dead == true)
			return (-1);
		pthread_mutex_unlock(&(*philo).table->print);
		if ((ft_get_time() - t_start) >= time)
			return (0);
		usleep(100);
	}
	(*philo).table->dead = true;
	pthread_mutex_lock(&(*philo).table->print);
	printf(PR"[%d] %d died\n"RES, ft_get_time(), (*philo).id);
	pthread_mutex_unlock(&(*philo).table->print);
	return (-1);
}

/*
*1st:	Checks if someone is dead.
*2nd:	Saves the time when function is called.
*3rd:	Prints the message.
*4th:	*/
int	eating(t_philo *philo)
{
	int	t_start_eating;

	if ((*philo).table->dead == true)
		return (-1);
	pthread_mutex_lock(&(*philo).table->print);
	printf(GR"[%d] %d is eating\n"RES, ft_get_time(), (*philo).id);
	pthread_mutex_unlock(&(*philo).table->print);
	if (uwait(&philo, (*philo).table->t_eat) == -1)
		return (-1);
	return (0);
}

int	ft_printer(t_philo *philo, char FLAG)
{
	if (FLAG == 'E')
	{
		eating(&philo);
	}
	return (0);
}
