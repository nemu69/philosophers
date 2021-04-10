/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:36:49 by nepage-l          #+#    #+#             */
/*   Updated: 2021/04/10 15:22:24 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_eat(t_phil *philo)
{
	int	nb;

	nb = (P->state.nb - 1 < 0 ? P->number_philo : 0);
	pthread_mutex_lock(&P[nb - 1].state.mutex);
	if (!ft_statenow(P, " has taken a fork\n"))
		return (0);
	pthread_mutex_lock(&P->state.mutex);
	if ((!ft_statenow(P, " has taken a fork\n") ||
	!(ft_statenow(P, " is eating\n"))))
		return (0);
	P->must_eat > 0 ? P->must_eat-- : 0;
	usleep(1000 * P->time_to_eat);
	last_graille(P);
	pthread_mutex_unlock(&P->state.mutex);
	pthread_mutex_unlock(&P[nb - 1].state.mutex);
	return (1);
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
	return (1);
}
