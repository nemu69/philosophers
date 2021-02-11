/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fucklanorme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:36:49 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/10 16:14:57 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			mlock(t_phil *philo, int code, int nbmut)
{
	int i;

	i = -1 - P->state.nb;
	if (nbmut)
		while (++i < (*P).number_philo - (P->state.nb + 1))
			code ? pthread_mutex_lock(&P[i].state.writemutex) :
				pthread_mutex_unlock(&P[i].state.writemutex);
	if (!nbmut)
		while (++i < (*P).number_philo - (P->state.nb + 1))
			code ? pthread_mutex_lock(&P[i].state.mutex) :
				pthread_mutex_unlock(&P[i].state.mutex);
	return (0);
}

int			free_all(t_phil *philo, char *str)
{
	int i;

	i = -1;
	while (++i < (*P).number_philo)
		pthread_mutex_destroy(&P[i].state.mutex);
	free(P);
	if (str)
		write(1, str, 23);
	return (0);
}

int			check_death(t_phil *philo)
{
	int i;

	i = -1 - P->state.nb;
	while (++i < (*P).number_philo - (P->state.nb + 1))
		if (!P[i].err)
		{
			P->err = 0;
			return (1);
		}
	return (0);
}

int			ft_statenow(t_phil *philo, char *str)
{
	mlock(P, 1, 1);
	if (check_death(P))
	{
		mlock(P, 0, 1);
		return (0);
	}
	if (!ft_must_eat(P))
	{
		mlock(P, 0, 1);
		return (0);
	}
	ft_putnbr(current_timestamp(P));
	write(1, " ", 1);
	ft_putnbr(P->state.nb + 1);
	write(1, " ", 1);
	ft_putstr(str);
	mlock(P, 0, 1);
	return (1);
}

int			ft_death(t_phil *philo, long long time)
{
	struct timeval	te;
	int				i;
	long long		timenow;

	mlock(P, 1, 0);
	gettimeofday(&te, NULL);
	i = -1 - P->state.nb;
	timenow = ((te.tv_sec * 1000LL) + (te.tv_usec / 1000));
	if (timenow - P->state.last_eat + time > P->time_to_die)
	{
		if (check_death(P))
			return (mlock(P, 0, 0));
		mlock(P, 0, 0);
		P->state.eating ?
		usleep(1000 * (P->time_to_die - (timenow - P->state.last_eat))) : 0;
		ft_statenow(P, " died\n");
		mlock(P, 1, 0);
		while (++i < (*P).number_philo - (P->state.nb + 1))
			P[i].err = 0;
		mlock(P, 0, 0);
		return (0);
	}
	mlock(P, 0, 0);
	return (1);
}
