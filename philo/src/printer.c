/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:46:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/24 20:10:55 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	printer(t_philo *philo, char flag)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (pthread_mutex_lock(&philo->table->print) != 0)
		return (-1);
	else if (flag == 'F')
		printf(CI"[%lu] %lu has taken a fork\n"RES, (ft_get_time() - philo->table->start_time), (*philo).id);
	else if (flag == 'E')
	{
		printf(GR"[%lu] %lu is eating\n"RES, (ft_get_time() - philo->table->start_time), (*philo).id);
		(*philo).meals++;
	}
	else if (flag == 'S')
		printf(PI"[%lu] %lu is sleeping\n"RES, (ft_get_time() - philo->table->start_time), (*philo).id);
	else if (flag == 'T')
		printf(FF"[%lu] %lu is thinking\n"RES, (ft_get_time() - philo->table->start_time), (*philo).id);
	if (pthread_mutex_unlock(&philo->table->print) != 0)
		return (-1);
	return (0);
}


int	printer_dead(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->print) != 0)
		return (-1);
	printf(RD"[%lu] %lu died\n"RES, (ft_get_time() - philo->table->start_time), philo->id);
	if (pthread_mutex_unlock(&philo->table->print) != 0)
		return (-1);
	return (0);
}
