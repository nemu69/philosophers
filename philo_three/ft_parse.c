/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/10 15:48:36 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	last_graille(t_phil *philo)
{
	struct timeval te;

	gettimeofday(&te, NULL);
	philo->state.last_eat = (te.tv_sec * 1000LL + te.tv_usec / 1000);
}

int		ft_atoi(const char *str)
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

int		ft_check_parse(int ac, t_phil **philo)
{
	(**philo).time_to_die < 60 ? ((**philo).err = 0) : 0;
	(**philo).time_to_eat < 60 ? ((**philo).err = 0) : 0;
	(**philo).time_to_sleep < 60 ? ((**philo).err = 0) : 0;
	if (ac == 6)
		(**philo).must_eat < 1 &&
		(**philo).must_eat != 1 ? ((**philo).err = 0) : 0;
	return ((**philo).err);
}

int		ft_parse(int ac, char **av, t_phil **philo)
{
	int				count;
	int				i;
	struct timeval	te;

	gettimeofday(&te, NULL);
	i = -1;
	count = ft_atoi(av[1]);
	while (++i < count)
	{
		(*philo)[i].err = 1;
		(*philo)[i].state.start_time = te.tv_sec * 1000LL + te.tv_usec / 1000;
		(*philo)[i].state.last_eat = (*philo)[i].state.start_time;
		(*philo)[i].state.nb = i;
		(*philo)[i].state.eating = 0;
		(*philo)[i].state.forkr = 1;
		(*philo)[i].time_to_die = ft_atoi(av[2]);
		(*philo)[i].time_to_eat = ft_atoi(av[3]);
		(*philo)[i].time_to_sleep = ft_atoi(av[4]);
		(*philo)[i].number_philo = count;
		(*philo)[i].must_eat = -2;
		if (ac == 6)
			(*philo)[i].must_eat = ft_atoi(av[5]);
	}
	return (ft_check_parse(ac, philo));
}
