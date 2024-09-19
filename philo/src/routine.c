/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:12:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/19 20:40:29 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_eat(t_philo *philo)
{
	if ((*philo).id != (*philo).table->n_philos)
	{
		if (pthread_mutex_lock(&(*philo).r_fork) != 0)
			return (-1);
		if (pthread_mutex_lock(&(*philo).l_fork) != 0)
			return (-1);
		(*philo).t_meals = ft_get_time();
		eating(&philo);
		if (pthread_mutex_unlock(&(*philo).r_fork) != 0)
			return (-1);
		if (pthread_mutex_unlock(&(*philo).l_fork) != 0)
			return (-1);
	}
	return (0);
}

int	ft_rest(&philo)
{//ft_mimir
//print(block mutex print)
//waiting
//check dead
}

int	ft_routine(void	*param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (((*philo).id % 2) == 0)
		usleep(100);
	while (1)
	{
		if (ft_eat(&philo) == -1)
			return (-1);
		if (ft_rest(&philo) == -1)
			return (-1);
		if (ft_think() == -1)
			return (-1);
	}
	return (0);
}

/*
En la rutina 
checkear muertos
cpger tenedores
primero el derecho y luego el izquierdo !!!salvo el ultimo lo haga al revés!!!
tiene que comer x milisegundos
dormir
etc
tengo que checkear muerte después de cada cambio de estado

todo en orden

*/

//en el think hay que hacer un uwait == tiempo de comer solo si son impares 