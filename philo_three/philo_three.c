/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/22 11:31:11 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_child(void *arg)
{
	t_phil	*philo;

	philo = arg;
	while (1)
	{
		if (!ft_death(P, 0))
			exit(1);
		if (philo->must_eat == -1)
			exit(0);
	}
}

void	*job(t_phil *philo)
{
	pthread_t	threads[1];

	last_graille(P);
	P->state.start_time = P->state.last_eat;
	if (pthread_create(&threads[0], NULL, check_child, philo) != 0)
		return (NULL);
	pthread_detach(threads[0]);
	while (1)
	{
		if (!ft_eat(philo))
			return (NULL);
	}
	return (NULL);
}

int		ft_mutex_global(t_phil **philo)
{
	int i;

	i = -1;
	if (((*philo)[0].state.sem =
				sem_open("/sem-mutex", O_CREAT, 0660, (*P)->number_philo))
			== SEM_FAILED)
		return (0);
	if (((*philo)[0].state.writesem =
				sem_open("/sem-wmutex", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (0);
	while (++i < (*philo)->number_philo)
	{
		(*philo)[i].state.sem = (*philo)[0].state.sem;
		(*philo)[i].state.writesem = (*philo)[0].state.writesem;
	}
	return (1);
}

int		ft_process(t_parent *papa)
{
	int			i;
	pid_t		info;

	i = -1;
	sem_unlink("/sem-mutex");
	sem_unlink("/sem-wmutex");
	if (!ft_mutex_global(&papa->philo))
		return (free_all(papa->philo, "sem init failed\n"));
	i = -1;
	while (++i < papa->philo->number_philo)
	{
		info = fork();
		if (info == -1)
			return (free_all(papa->philo, "fork init failed\n"));
		else if (info == 0)
			job(&papa->philo[i]);
		papa->philo[i].state.child = info;
	}
	return (ft_status(papa));
}

int		main(int ac, char **av)
{
	t_parent *papa;

	if (!((ac == 5 || ac == 6) && ft_atoi(av[1]) > 0))
		return (write(1, "Error numbers arguments\n", 24));
	if (!(papa = (t_parent *)ft_calloc(1, sizeof(t_parent))))
		return (0);
	if (!(papa->philo =
		(t_phil *)ft_calloc(ft_atoi(av[1]) + 1, sizeof(t_phil))))
		return (0);
	if (!(ft_parse(ac, av, &papa->philo)))
		return (write(1, "Error arguments value\n", 22));
	return (ft_process(papa));
}
