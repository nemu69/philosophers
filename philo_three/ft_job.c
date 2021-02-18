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

#include "philo_three.h"

int		ft_must_eat(t_phil *philo)
{
	int	i;

	slock(P, 1, 0);
	if (check_death(P))
		return (slock(P, 0, 0));
	i = 0 - P->state.nb;
	while (i < (((*P).number_philo - P->state.nb) + 1) && !P[i].must_eat)
		i++;
	if (i == ((*P).number_philo - P->state.nb) + 1)
	{
		i = -1 - P->state.nb;
		while (++i < (*P).number_philo - (P->state.nb + 1))
			P[i].err = 0;
		slock(P, 0, 0);
		return (0);
	}
	slock(P, 0, 0);
	return (1);
}

int		ft_eat(t_phil *philo)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " has taken a fork\n")))
		return (0);
	if (!(ft_statenow(P, " has taken a fork\n")))
		return (0);
	if (!(ft_statenow(P, " is eating\n")))
		return (0);
	slock(philo, 0, 0);
	P->must_eat--;
	usleep(1000 * P->time_to_eat);
	// slock(philo, 0, 0);
	// slock(philo, 1, 0);
	last_graille(P);
	// usleep(1000); optionel
	return (ft_sleep(philo));

}

int		ft_think(t_phil *philo)
{
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " is thinking\n")))
		return (0);
	slock(philo, 0, 0);
	return (1);
}

int		ft_sleep(t_phil *philo)
{
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " is sleeping\n")))
		return (0);
	usleep(1000 * P->time_to_sleep);
	slock(philo, 0, 0); 
	return (ft_think(philo));
}
