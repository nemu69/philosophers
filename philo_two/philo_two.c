/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/04/17 18:39:13 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			check_child(t_phil *philo)
{
	int i;

	while (1)
	{
		i = -1;
		while (i < (*P).number_philo && !P[++i].must_eat)
			;
		if (i == (*P).number_philo && slock(P, 1, 1))
			return (1);
		i = -1;
		while (++i < (*P).number_philo)
		{
			if (!ft_death(&P[i], 0) && slock(P, 1, 1))
				return (0);
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
			{
				slock(P, 0, 1);
				slock(P, 0, 0);
				return (NULL);
			}
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
	ft_mutex_global(&philo);
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
