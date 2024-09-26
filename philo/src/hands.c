/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:43 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/26 21:26:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***********************************************************************
*This are the hands of the philosophers.                               *
*1st:	Lock the fork.                                                 *
*2nd:	Print the sentence for eating.                                 *
*			If someone is dead or anything fails(-1) unlocks the mutex.*
***********************************************************************/
int	ft_r_hand(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (-1);
	if (printer(philo, 'F') == -1)
	{
		if (philo->id == philo->table->n_philos)
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (-1);
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			return (-1);
		}
	}
	return (0);
}

int	ft_l_hand(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (-1);
	if (printer(philo, 'F') == -1)
	{
		if (philo->id == philo->table->n_philos)
		{
			pthread_mutex_unlock(philo->l_fork);
			return (-1);
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (-1);
		}
	}
	return (0);
}

int	ft_last_one(t_philo *philo)
{
	if (philo->id == philo->table->n_philos)
	{
		if (ft_l_hand(philo) == -1)
			return (-1);
		if (ft_r_hand(philo) == -1)
			return (-1);
	}
	else
	{
		if (ft_r_hand(philo) == -1)
			return (-1);
		if (ft_l_hand(philo) == -1)
			return (-1);
	}
	return (0);
}
