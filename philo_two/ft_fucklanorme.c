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

#include "philo_two.h"

int			slock(t_phil *philo, int code, int nbmut)
{
	if (nbmut)
			code ? sem_wait(P->state.writesem) :
				sem_post(P->state.writesem);
	if (!nbmut)
			code ? sem_wait(P->state.sem) :
				sem_post(P->state.sem);
	return (0);
}

int			free_all(t_phil *philo, char *str)
{
	int i;

	i = -1;
	while (++i < (*P).number_philo)
		sem_unlink("/sem-mutex");
	while (++i < (*P).number_philo)
		sem_unlink("/sem-wmutex");
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
	slock(P, 1, 1);
	if (check_death(P))
	{
		slock(P, 0, 1);
		return (0);
	}
	// if (!ft_must_eat(P))
	// {
	// 	slock(P, 0, 1);
	// 	return (0);
	// }
	ft_putnbr(current_timestamp(P));
	write(1, " ", 1);
	ft_putnbr(P->state.nb + 1);
	write(1, " ", 1);
	ft_putstr(str);
	slock(P, 0, 1);
	return (1);
}

int			ft_death(t_phil *philo, long long time)
{
	struct timeval	te;
	int				i;
	long long		timenow;


	slock(P, 1, 0);
	gettimeofday(&te, NULL);
	i = -1 - P->state.nb;
	timenow = ((te.tv_sec * 1000LL) + (te.tv_usec / 1000));
	if (timenow - P->state.last_eat + time > P->time_to_die)
	{
		if (check_death(P))
			return (slock(P, 0, 0));
		slock(P, 0, 0);
		P->state.eating ?
		usleep(1000 * (P->time_to_die - (timenow - P->state.last_eat))) : 0;
		ft_statenow(P, " died\n");
		slock(P, 1, 0);
		while (++i < (*P).number_philo - (P->state.nb + 1))
			P[i].err = 0;
		slock(P, 0, 0);
		return (0);
	}
	slock(P, 0, 0);
	return (1);
}
