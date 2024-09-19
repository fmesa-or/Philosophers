/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:21:12 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/19 20:34:15 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/* COLORS */
# define RD			"\033[1;91m"
# define GR			"\033[0;92m"
# define PR			"\033[4;95m"
# define YL			"\033[0;93m"
# define RES		"\033[0m"

	/* STRUCTURE */

/************************************************************************
*n_philos : number of philosophers and forks                            *
*t_die : time(ms) to die from meal to meal                              *
*t_eat : time(ms) spending eating                                       *
*t_sleep : time(ms) spending sleeping                                   *
*meals : if every philosopher eats this amount of meals the program ends*
************************************************************************/
typedef struct s_table
{
	unsigned long	n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	unsigned long	start_time;
	bool			dead;

}	t_table;

/*****************************************
*id : id number                          *
*thread : the thread for this philosopher*
*table : the table                       *
*l_fork : close fork                     *
*r_fork : own fork                       *
*meals : how many meals has eaten        *
*t_meal : machine time when eating        *
*****************************************/
typedef struct s_philo
{
	unsigned long	id;
	pthread_t		thread;
	t_table			*table;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	unsigned long	meals;
	unsigned long	t_meals;

}	t_philo;


/* MAIN */

/* UTILS */
int	ft_isdigit(char *str);
int	check_parse(int ac, char **av);
unsigned long	ft_get_time();
int	eating(t_philo *philo);



/* MAÎTRE */
int	create_table(char **av, t_table *table);
int	create_philo(char **av, t_table *table, t_philo *philo);

/* THREADS */
int	create_threads(t_table *table, t_philo *philo);
int	join_threads(t_philo *philo);

/* ROUTINE */
int ft_routine(void	*param);


#endif