/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fucklanorme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:36:49 by nepage-l          #+#    #+#             */
/*   Updated: 2021/04/17 17:06:26 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			free_all(t_phil *philo, char *str)
{
	int i;

	i = -1;
	while (++i < (*P).number_philo)
		sem_unlink("/sem-mutex");
	i = -1;
	while (++i < (*P).number_philo)
		sem_unlink("/sem-wmutex");
	if (str)
		write(1, str, 23);
	free(P);
	return (0);
}

int			check_death(t_phil *philo)
{
	int i;

	i = -1 - P->state.nb;
	while (++i < (*P).number_philo - P->state.nb)
		if (!P[i].err)
		{
			P->err = 0;
			return (1);
		}
	return (0);
}

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && (s2[i] != '\0' || s1[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

int			ft_statenow(t_phil *philo, char *str)
{
	if (P->must_eat != -1)
	{
		slock(P, 1, 1);
		ft_putnbr(current_timestamp(P));
		write(1, " ", 1);
		ft_putnbr(P->state.nb + 1);
		write(1, " ", 1);
		ft_putstr(str);
		!ft_strcmp(" died\n", str) ? 0 : slock(P, 0, 1);
	}
	return (1);
}

int			ft_death(t_phil *philo, long long time)
{
	struct timeval	te;
	long long		timenow;

	gettimeofday(&te, NULL);
	timenow = ((te.tv_sec * 1000LL) + (te.tv_usec / 1000));
	if (timenow - P->state.last_eat + time > P->time_to_die)
	{
		ft_statenow(P, " died\n");
		P->err = 0;
		return (0);
	}
	return (1);
}
