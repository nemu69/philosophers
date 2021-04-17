/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/04/17 15:28:07 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			check_child(t_phil *philo)
{
	int i;

	while (1)
	{
		i = -1;
		while (i < (*P).number_philo && !P[++i].must_eat)
			;
		if (i == (*P).number_philo)
		{
			mlock(P, 1, 1);
			return (1);
		}
		i = -1;
		while (++i < (*P).number_philo)
		{
			if (!ft_death(&P[i], 0))
			{
				mlock(P, 1, 1);
				return (0);
			}
		}
	}
}

void		*job(void *arg)
{
	t_phil *philo;

	P = arg;
	while (1)
	{
		while (P->must_eat != 0)
		{
			if (!ft_eat(P))
				return (NULL);
			if (!ft_sleep(P))
				return (NULL);
			if (!ft_think(P))
				return (NULL);
		}
	}
}

int			ft_init_mutex(t_phil *philo)
{
	int			i;

	i = -1;
	while (++i < (*P).number_philo)
		if (pthread_mutex_init(&P[i].state.mutex, NULL) != 0)
			return (0);
	if (pthread_mutex_init(&P[0].state.writemutex, NULL) != 0)
		return (0);
	return (1);
}

int			ft_threads(t_phil *philo)
{
	pthread_t	threads[(*P).number_philo];
	int			i;

	i = -1;
	if (!ft_init_mutex(philo))
		return (free_all(philo, "mutex init failed\n"));
	while (++i < (*P).number_philo)
	{
		if (pthread_create(&threads[i], NULL, job, &P[i]) != 0)
			return (free_all(philo, "thread init failded\n"));
		pthread_detach(threads[i]);
		usleep(50);
	}
	if (check_child(P))
		return (free_all(P, "Philo is bien graille\n"));
	return (free_all(P, NULL));
}

int			main(int ac, char **av)
{
	t_phil	*philo;

	if (!((ac == 5 || ac == 6) && ft_atoi(av[1]) > 1))
		return (write(1, "Error numbers arguments\n", 24));
	if (!(P = (t_phil *)ft_calloc(ft_atoi(av[1]) + 1, sizeof(t_phil))))
		return (0);
	if (!(ft_parse(ac, av, &P)))
		return (write(1, "Error arguments value\n", 22));
	return (ft_threads(philo));
}
