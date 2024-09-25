/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:12:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/25 14:30:47 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/***************************************************************************************
*time	= Amount of time necesary to complette the task.                               *
*--------------------------------------------------------------------------------------*
*1st:	Saves time starting the task.                                                  *
*2nd:	While the philosopher is alive checks if someone died, checks if it's          *
*			done with the task and waits to start the loop again.                      *
*			Only get's out of the loop if he dies or someone died.                     *
*3rd:	If the philosopher dies making the task:                                       *
*		3.1:	Locks the reaper so it can check if someone died already.(Protection). *
*		3.2:	Changes the dead bool from false to true.                              *
*		3.3:	Prints the dead message, and unlock the mutex.                         *
*--------------------------------------------------------------------------------------*
*Remember:	The spawn of life time is mesured with the last time the philosopher eated.*
***************************************************************************************/
int	uwait(t_philo *philo, unsigned long time)
{
	unsigned long	t_start;

	t_start = ft_get_time();
	if (ft_graveyard(philo) == -1)
		return (-1);
	while ((ft_get_time() - (*philo).t_meals) < (*philo).table->t_die)
	{
		if (ft_graveyard(philo) == -1)
			return (-1);
		if ((ft_get_time() - t_start) >= time)
			return (0);
		usleep(10000);
	}
	pthread_mutex_lock(&philo->table->reaper);
	if (philo->table->dead == true)
	{
		pthread_mutex_unlock(&philo->table->reaper);
		return (-1);
	}
	philo->table->dead = true;
	if (printer_dead(philo) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->table->reaper);
	return (-1);
}

/*****************************************************************************
*1st:	Checks if someone is dead.                                           *
*2nd:	Prints the message.                                                  *
*3rd:	Locks the reaper to add one more seated philosopher if it's needed.  *
*4th:	If all the philosophers are seated, it uses dead to end every thread.*
*			If not, unlock the reaper mutex anyways and send to uwait.       *
*****************************************************************************/
int	eating(t_philo *philo)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (printer(philo, 'E') == -1)
		return (-1);
	pthread_mutex_lock(&philo->table->reaper);
	if (philo->meals == philo->table->meals)
		philo->table->sated++;
	if (philo->table->sated == philo->table->n_philos)
	{
		philo->table->dead = true;
		pthread_mutex_unlock(&philo->table->reaper);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->reaper);
	if (uwait(philo, philo->table->t_eat) == -1)
		return (-1);
	return (0);
}

/*******************************************************************
*1st:	Check if someone is dead.                                  *
*2nd:	Tooks the right fork.                                      *
*3rd:	Tooks the left fork.                                       *
*4th:	Updates the last time the philosopher eated.               *
*5th:	Send to subfunction eating to make more checks and process.*
*6th:	Unlocks the forks despite the return of eating.            *
*******************************************************************/
int	ft_eat(t_philo *philo)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (ft_hand(philo, 'r') == -1)
		return (-1);
	if (ft_hand(philo, 'l') == -1)
		return (-1);
	philo->t_meals = ft_get_time();
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

/*******************************************************************************
*1st:	Checks if someone is dead.                                             *
*2nd:	Prints the sleeping message.                                           *
*3rd:	Waits the sleeping time said.                                          *
*4th:	Prints the thinking message.                                           *
*5th:	If t_eat is diffrent from t_sleep, we speend eating the amount of time *
*			needed for the others to finish eating.                            *
*			This is for be more accurated to dead.                             *
*******************************************************************************/
int	ft_rest(t_philo *philo)
{
	if (ft_graveyard(philo) == -1)
		return (-1);
	if (printer(philo, 'S') == -1)
		return (-1);
	if (uwait(philo, philo->table->t_sleep) == -1)
		return (-1);
	if (printer(philo, 'T') == -1)
		return (-1);
	if (philo->table->t_eat > philo->table->t_sleep)
	{
		if (uwait(philo, (philo->table->t_eat - philo->table->t_sleep)) == -1)
			return (-1);
	}
	else if (philo->table->t_eat < philo->table->t_sleep)
	{
		if (uwait(philo, (philo->table->t_sleep - philo->table->t_eat)) == -1)
			return (-1);
	}
	return (0);
}

/****************************************************
*1st:	We cast the philosopher pointer.            *
*2nd:	We set turns for start so the threads flow. *
*3rd:	Unles someone is dead or something fails we:*
*		3.1:	Check if someone is dead.           *
*		3.2:	Eat.                                *
*		3.3:	Sleep and think.                    *
****************************************************/
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
	}
	return (0);
}
