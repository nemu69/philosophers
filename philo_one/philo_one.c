/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/11 13:22:31 by nepage-l         ###   ########lyon.fr   */
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
			return (NULL);
		}
		P->state.eating = 0;
		if (!ft_sleep(P))
		{
			mlock(P, 1, 0);
			mlock(P, 0, 0);
			return (NULL);
		}
		if (!ft_think(P))
		{
			mlock(P, 1, 0);
			mlock(P, 0, 0);
			return (NULL);
		}
	}
}

int			ft_threads(t_phil *philo)
{
	pthread_t	threads[(*P).number_philo];
	int			i;

	i = -1;
	if (pthread_mutex_init(&P[0].state.mutex, NULL) != 0)
		return (free_all(philo, "mutex init failed\n"));
	if (pthread_mutex_init(&P[0].state.writemutex, NULL) != 0)
		return (free_all(philo, "mutex init failed\n"));
	while (++i < (*P).number_philo)
		if (pthread_create(&threads[i], NULL, job, &P[i]) != 0)
			return (free_all(philo, "thread init failded\n"));
	i = -1;
	while (++i < (*P).number_philo)
		pthread_join(threads[i], NULL);
	i = -1;
	while (!P[++i].must_eat && i < (*P).number_philo - (P->state.nb + 1))
		;
	if (i == (*P).number_philo - (P->state.nb + 1))
		return (free_all(P, "Philo is bien graille\n"));
	return (free_all(P, NULL));
}

int			main(int ac, char **av)
{
	t_phil	*philo;

	if (!((ac == 5 || ac == 6) && ft_atoi(av[1]) > 0))
		return (write(1, "Error numbers arguments\n", 24));
	if (!(P = (t_phil *)ft_calloc(ft_atoi(av[1]) + 1, sizeof(t_phil))))
		return (0);
	if (!(ft_parse(ac, av, &P)))
		return (write(1, "Error arguments value\n", 22));
	return (ft_threads(philo));
}
