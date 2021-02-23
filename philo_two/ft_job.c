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

#include "philo_two.h"

int		ft_eat(t_phil *philo)
{
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " has taken a fork\n")))
		return (0);
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " has taken a fork\n")))
		return (0);
	if (!(ft_statenow(P, " is eating\n")))
		return (0);
	if (!ft_death(P, P->time_to_eat))
	{
		P->must_eat = -5;
		return (0);
	}
	P->must_eat--;
	usleep(1000 * P->time_to_eat);
	slock(philo, 0, 0);
	slock(philo, 0, 0);
	last_graille(P);
	return (ft_sleep(philo));
}

int		ft_think(t_phil *philo)
{
	if (!(ft_statenow(P, " is thinking\n")))
		return (0);
	return (1);
}

int		ft_sleep(t_phil *philo)
{
	if (!(ft_statenow(P, " is sleeping\n")))
		return (0);
	usleep(1000 * P->time_to_sleep);
	return (ft_think(philo));
}

int		slock(t_phil *philo, int code, int nbmut)
{
	if (nbmut)
		code ? sem_wait(P->state.writesem) :
			sem_post(P->state.writesem);
	if (!nbmut)
		code ? sem_wait(P->state.sem) :
			sem_post(P->state.sem);
	return (0);
}
