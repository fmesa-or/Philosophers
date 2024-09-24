/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:12:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/24 20:38:10 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_eat(t_philo *philo)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (ft_hand(philo, 'r') == -1)
		return (-1);
	if (ft_hand(philo, 'l') == -1)
		return (-1);
	(*philo).t_meals = ft_get_time();
	if (eating(philo) == -1)
	{
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (-1);
		if (pthread_mutex_unlock(philo->l_fork) != 0)
			return (-1);
		return (-1);
	}
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (-1);
	return (0);
}

int	ft_rest(t_philo *philo)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (printer(philo, 'S') == -1)
		return (-1);
	if (uwait(&(*philo), (*philo).table->t_sleep) == -1)
		return (-1);
	if (printer(philo, 'T') == -1)
		return (-1);
	return (0);
}

void	*ft_routine(void	*param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (((philo)->id % 2) == 0)
		usleep(100);
	while (1)
	{
		if (ft_graveyard(philo) == -1)
			break ;
		if (ft_eat(&(*philo)) == -1)
			break ;
		if (ft_rest(&(*philo)) == -1)
			break ;
		if (philo->id % 2 == 0)
			usleep(100);
	}
	return (0);
}
