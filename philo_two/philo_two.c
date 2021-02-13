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

#include "philo_two.h"

void		*job(void *arg)
{
	t_phil *philo;

	P = arg;
	while (1)
	{
		if (!ft_eat(P))
		{
			slock(P, 1, 0);
			slock(P, 0, 0);
			pthread_exit(NULL);
		}
		P->state.eating = 0;
		if (!ft_sleep(P))
		{
			slock(P, 1, 0);
			slock(P, 0, 0);
			pthread_exit(NULL);
		}
		if (!ft_think(P))
		{
			slock(P, 1, 0);
			slock(P, 0, 0);
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
		(*P)[i].state.sem = (*P)[0].state.sem;
		(*P)[i].state.writesem = (*P)[0].state.writesem;
	}
}

int			ft_threads(t_phil *philo)
{
	pthread_t	threads[(*P).number_philo];
	int			i;

	i = -1;
	sem_unlink("/sem-mutex");
	if ((P[0].state.sem =
	sem_open("/sem-mutex", O_CREAT, 0660, philo->number_philo)) == SEM_FAILED)
		return (free_all(philo, "sem init failed\n"));
	sem_unlink("/sem-wmutex");
	if ((P[0].state.writesem =
	sem_open("/sem-wmutex", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (free_all(philo, "sem init failed\n"));
	while (++i < (*P).number_philo)
		if (pthread_create(&threads[i], NULL, job, &P[i]) != 0)
			return (free_all(philo, "thread init failded\n"));
	ft_mutex_global(&philo);
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
