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

int		ft_must_eat(t_phil *philo)
{
	int	i;

	mlock(P, 1, 0);
	if (check_death(P))
		return (mlock(P, 0, 0));
	i = 0 - P->state.nb;
	while (i < (((*P).number_philo - P->state.nb) + 1) && !P[i].must_eat)
		i++;
	if (i == ((*P).number_philo - P->state.nb) + 1)
	{
		i = -1 - P->state.nb;
		while (++i < (*P).number_philo - (P->state.nb + 1))
			P[i].err = 0;
		mlock(P, 0, 0);
		return (0);
	}
	mlock(P, 0, 0);
	return (1);
}

int		ft_eat(t_phil *philo)
{
	int				nb;
	struct timeval	te;

	gettimeofday(&te, NULL);
	nb = (P->state.nb - 1 < 0 ? P->number_philo : 0);
	while (!philo->state.eating && ft_death(P, 0))
	{
		if (!P[nb - 1].state.eating && P[nb - 1].state.forkr && P->state.forkr)
		{
			P->state.eating = 1;
			P[nb - 1].state.forkr = 0;
			if (!(ft_statenow(P, " has taken a fork\n") &&
			ft_statenow(P, " has taken a fork\n")))
				return (0);
			if (!ft_death(P, P->time_to_eat))
				return (0);
			if (!(ft_statenow(P, " is eating\n")))
				return (0);
			P->must_eat--;
			usleep(1000 * P->time_to_eat);
			last_graille(P);
			P[nb - 1].state.forkr = 1;
			usleep(1000);
			return (ft_must_eat(philo));
		}
	}
	return (P->err);
}

int		ft_think(t_phil *philo)
{
	if (!ft_death(P, 0))
		return (0);
	if (!(ft_statenow(P, " is thinking\n")))
		return (0);
	return (1);
}

int		ft_sleep(t_phil *philo)
{
	if (!ft_death(P, 0))
		return (0);
	if (!(ft_statenow(P, " is sleeping\n")))
		return (0);
	usleep(1000 * P->time_to_sleep);
	return (1);
}
