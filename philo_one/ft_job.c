/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:36:49 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/10 17:36:55 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_eat(t_phil *philo)
{
	int nb;

	nb = (philo->state.nb - 1 < 0 ? philo->number_philo : 0);
	while (!philo->state.eating && ft_death(philo, 0))
	{
		if (!philo[nb - 1].state.eating && philo[nb - 1].state.forkr
		&& philo->state.forkr)
		{
			philo->state.eating = 1;
			philo[nb - 1].state.forkr = 0;
			if (!(ft_statenow(philo, " has taken a fork\n")))
				return (0);
			if (!(ft_statenow(philo, " has taken a fork\n")))
				return (0);
			if (!(ft_statenow(philo, " is eating\n")))
				return (0);
			last_graille(philo);
			usleep(1000 * philo->time_to_eat);
			ft_death(philo, philo->time_to_eat);
			philo[nb - 1].state.forkr = 1;
		}
	}
	return (philo->err);
}

int			ft_think(t_phil *philo)
{
	if (!ft_death(P, 0))
		return (0);
	if (!(ft_statenow(P, " is thinking\n")))
		return (0);
	return (1);
}

int			ft_sleep(t_phil *philo)
{
	if (!ft_death(P, 0))
		return (0);
	if (!(ft_statenow(P, " is sleeping\n")))
		return (0);
	usleep(1000 * P->time_to_sleep);
	return (1);
}
