/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:48:20 by oceanscore        #+#    #+#             */
/*   Updated: 2024/09/23 20:41:42 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atoul(const char *str)
{
	long			i;
	unsigned long	n;

	i = 0;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
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

int	ft_diner_4_1(t_philo *philo, t_table *table)
{
	printf(CI"[%lu] %lu has taken a fork\n"RES, (ft_get_time() - philo->table->start_time), philo->id);
	usleep(philo->table->t_die * 1000);
	printf(RD"[%lu] %lu died\n"RES, (ft_get_time() - philo->table->start_time), philo->id);
	free(table);
	free(philo);
	return (-1);
}

int	ft_graveyard(t_philo *philo)
{
	if (ft_get_time() - philo->t_meals >= philo->table->t_die)
		philo->table->dead = true;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->dead == true)
	{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}
