/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:28:29 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/09/26 20:08:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**************************************************************
*If the sring send is a positive number returns 0, in font -1.*
**************************************************************/
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

/*******************************************
*Checks if the input arguments are correct.*
*******************************************/
int	check_parse(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf(RD"ERROR: Wrong amount of arguments.\n");
		return (-1);
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
			if (ft_value_0(ft_atoul(av[i])) == -1)
				return (-1);
		}
	}
	return (0);
}

/*************************************************************************
*Small protection for smart people trying to get down this proyect easily*
*************************************************************************/
int	ft_value_0(unsigned long value)
{
	if (value == 0)
	{
		printf("Nice try...\n");
		printf(RD"Error: Values must be bigger than 0.\n"RES);
		return (-1);
	}
	return (0);
}
