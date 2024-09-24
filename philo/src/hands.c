/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:43 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/24 19:59:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_hand(t_philo *philo, char flag)
{
	if (flag == 'r')
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (-1);
		if (printer(philo, 'F') == -1)
		{
			pthread_mutex_unlock(philo->r_fork);
			return (-1);
		}
	}
	else if (flag == 'l')
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return (-1);
		if (printer(philo, 'F') == -1)
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (-1);
		}
	}
	return (0);
}