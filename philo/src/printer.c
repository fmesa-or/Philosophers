/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:46:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/26 19:43:56 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*********************************************************
*Prints the message intended by the flag given.          *
*1st:	Checks if someone is dead                        *
*2nd:	Locks the print mutex.                           *
*3rd:	prints the correct message following the flag.   *
*			If it was eating it adds one more meal eaten.*
*4th:	Unlocks the mutex.                               *
*********************************************************/
int	printer(t_philo *philo, char flag)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (pthread_mutex_lock(&philo->table->print) != 0)
		return (-1);
	if (flag == 'F')
		printf(CI"[%lu] %lu has taken a fork\n"RES,
			(ft_get_time() - philo->table->start_time), (*philo).id);
	else if (flag == 'E')
	{
		printf(GR"[%lu] %lu is eating\n"RES,
			(ft_get_time() - philo->table->start_time), (*philo).id);
		(*philo).meals++;
	}
	else if (flag == 'S')
		printf(PI"[%lu] %lu is sleeping\n"RES,
			(ft_get_time() - philo->table->start_time), (*philo).id);
	else if (flag == 'T')
		printf(FF"[%lu] %lu is thinking\n"RES,
			(ft_get_time() - philo->table->start_time), (*philo).id);
	if (pthread_mutex_unlock(&philo->table->print) != 0)
		return (-1);
	return (0);
}

/********************************************************************
*Special function for print the DEAD message.                       *
*The diffrence is that it doesn't checks if someone is dead         *
*	(we are at this point because we ALREADY know thath someone is).*
********************************************************************/
int	printer_dead(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->print) != 0)
		return (-1);
	printf(RD"[%lu] %lu died\n"RES,
		(ft_get_time() - philo->table->start_time), philo->id);
	if (pthread_mutex_unlock(&philo->table->print) != 0)
		return (-1);
	return (0);
}
