/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/01/30 14:13:53 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_atoi(const char *str)
{
	int i;
	int nbr;
	int negative;

	nbr = 0;
	negative = 1;
	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
			(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		nbr *= 10;
		nbr += (int)str[i] - '0';
		i++;
	}
	return (nbr * negative);
}

int	ft_check_parse(int ac, t_phil *philo)
{
	if (ac == 5)
	{
		philo->number_philo < 1 ? (philo->err = 0) : 0;
		philo->time_to_die < 60 ? (philo->err = 0) : 0;
		philo->time_to_eat < 60 ? (philo->err = 0) : 0;
		philo->time_to_sleep < 60 ? (philo->err = 0) : 0;
	}
	else if (ac == 6)
	{
		philo->number_philo < 1 ? (philo->err = 0) : 0;
		philo->time_to_die < 60 ? (philo->err = 0) : 0;
		philo->time_to_eat < 60 ? (philo->err = 0) : 0;
		philo->time_to_sleep < 60 ? (philo->err = 0) : 0;
		philo->number_of_time_philo_must_eat < 60 ? (philo->err = 0) : 0;
	}
	return (philo->err);
}

int	ft_parse(int ac, char **av, t_phil *philo)
{
	philo->err = 1;
	if (ac == 5)
	{
		philo->number_philo = ft_atoi(av[1]);
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_to_eat = ft_atoi(av[3]);
		philo->time_to_sleep = ft_atoi(av[4]);
	}
	else if (ac == 6)
	{
		philo->number_philo = ft_atoi(av[1]);
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_to_eat = ft_atoi(av[3]);
		philo->time_to_sleep = ft_atoi(av[4]);
		philo->number_of_time_philo_must_eat = ft_atoi(av[5]);
	}
	return (ft_check_parse(ac, philo));
}
