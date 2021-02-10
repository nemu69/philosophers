/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/10 16:17:11 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		*job(void *arg)
{
	t_phil *philo;

	P = arg;
	while (1)
	{
		if (!ft_eat(P))
		{
			mlock(P, 1, 0);
			mlock(P, 0, 0);
			pthread_exit(NULL);
		}
		P->state.eating = 0;
		if (!ft_sleep(P))
		{
			mlock(P, 1, 0);
			mlock(P, 0, 0);
			pthread_exit(NULL);
		}
		if (!ft_think(P))
		{
			mlock(P, 1, 0);
			mlock(P, 0, 0);
			pthread_exit(NULL);
		}
	}
}

void		ft_mutex_global(t_phil **philo)
{
	int i;

	i = 0;
	while (++i < (*P)->number_philo)
	{
		(*P)[i].state.mutex = (*P)[0].state.mutex;
		(*P)[i].state.writemutex = (*P)[0].state.writemutex;
	}
}

int			ft_threads(t_phil *philo)
{
	pthread_t	threads[(*P).number_philo];
	int			i;

	i = -1;
	if (pthread_mutex_init(&P[0].state.mutex, NULL) != 0)
		return (write(1, "mutex init failed", 18));
	if (pthread_mutex_init(&P[0].state.writemutex, NULL) != 0)
		return (write(1, "mutex init failed", 18));
	ft_mutex_global(&P);
	while (++i < (*P).number_philo)
		if (pthread_create(&threads[i], NULL, job, &P[i]) != 0)
			return (write(1, "thread init failded", 20));
	i = -1;
	while (++i < (*P).number_philo)
		pthread_join(threads[i], NULL);
	free_all(P);
	return (0);
}

int			main(int ac, char **av)
{
	t_phil	*philo;

	if (!((ac == 5 || ac == 6) && ft_atoi(av[1]) > 0))
		return (write(1, "Error numbers arguments", 24));
	if (!(P = (t_phil *)ft_calloc(ft_atoi(av[1]) + 1, sizeof(t_phil))))
		return (0);
	if (!(ft_parse(ac, av, &P)))
		return (write(1, "Error arguments value", 22));
	return (ft_threads(philo));
}
