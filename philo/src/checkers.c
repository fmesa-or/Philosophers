/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:28:29 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/24 20:37:30 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isundigit(char *str)
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
	{
		printf(RD"ERROR: Wrong amount of arguments.\n");
		return(-1);
	}
	else
	{
		while (++i < ac)
		{
			if ((ft_isundigit(av[i])) == -1)
			{
				printf(RD"Error:\tWrong input.\n"PR"Ex:\t./philo " \
					"(philosophers) (time_to_die) (eat_time) (sleep_time) " \
					"[target_meals]\n"RES);
				return (-1);
			}
		}
	}
	return(0);
}

int	ft_n_meals(t_table *table)
{
	if (table->meals == 0)
	{
		printf("Nice try...\n"RD"Error: Target meals must be bigger than 0.\n"RES);
		return (-1);
	}
	return (0);
}

