/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fucklanorme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:36:49 by nepage-l          #+#    #+#             */
/*   Updated: 2021/04/10 16:03:19 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			free_all(t_phil *philo, char *str)
{
	int i;

	i = -1;
	while (++i < (*P).number_philo)
		sem_unlink("/sem-mutex");
	i = -1;
	while (++i < (*P).number_philo)
		sem_unlink("/sem-wmutex");
	free(P);
	if (str)
		write(1, str, 23);
	return (0);
}

int			ft_statenow(t_phil *philo, char *str)
{
	slock(P, 1, 1);
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
	long long		timenow;

	gettimeofday(&te, NULL);
	timenow = ((te.tv_sec * 1000LL) + (te.tv_usec / 1000));
	if (timenow - P->state.last_eat + time > P->time_to_die + 5)
	{
		ft_statenow(P, " died\n");
		P->err = 0;
		return (0);
	}
	return (1);
}
