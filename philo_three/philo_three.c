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

#include "philo_three.h"

void		*check_child(void *arg)
{
	t_phil	*philo;
	int		nb;

	philo = arg;
	nb = 0;
	while (1)
	{

		// dprintf(1, "\nforknhilo : %d, eat : %ld\n", philo[0].state.nb, philo[0].must_eat);
		if (philo->state.eating)
		{
			P[nb - 1].state.forkr = 0;
			if (!ft_death(P, P->time_to_eat))
				return (NULL);
		}
		// if (!ft_death(P, 0))
		// slock(P, 0, 0);
		// 	return (NULL);
	}
}

int			ft_fini(t_parent *papa)
{
	// pthread_t	threads;
	// int			i;
	while (1){
			dprintf(1, "\nthhilo : %d, eat : %ld\n", papa->philo[0].state.nb, papa->philo[0].must_eat);

			return(free_all(papa->philo, NULL));
	}
	// i = -1;
	// // while (++i < papa->philo->number_philo)
	// // 	if (pthread_create(&threads[i], NULL, check_child, &papa->philo[i]) != 0)
	// // 		return (free_all(papa->philo, "thread init failded\n"));
	// // i = -1;
	// // while (++i < papa->philo->number_philo)
	// // 	pthread_join(threads[i], NULL);
	// // 	i = -1;
	// if (pthread_create(&threads[i], NULL, check_child, &papa) != 0)
	// 	return (free_all(papa->philo, "thread init failded\n"));
	// pthread_join(&threads[i], NULL);
	// while (!papa->philo[++i].must_eat && i < papa->philo->number_philo - (papa->philo->state.nb + 1))
	// 	;
	// if (i == papa->philo->number_philo - (papa->philo->state.nb + 1))
	// 	return (free_all(papa->philo, "Philo is bien graille\n"));
	return (free_all(papa->philo, NULL));
}

void		*job(t_phil	*philo)
{
	pthread_t	threads[1];

	if (pthread_create(&threads[0], NULL, check_child, philo) != 0)
			return (NULL);
	pthread_detach(threads[0]);

	while (1)
	{

		if (!ft_eat(philo))
		{
			slock(philo, 1, 0);
			slock(philo, 0, 0);			
			return (NULL);
		}
		philo->state.eating = 0;
	}
		return(NULL);
}

void		ft_mutex_global(t_phil **philo)
{
	int i;

	i = -1;

	while (++i < (*philo)->number_philo)
	{
		(*philo)[i].state.sem = (*philo)[0].state.sem;
		(*philo)[i].state.writesem = (*philo)[0].state.writesem;
	}
	sem_wait((*P)->state.sem);
	sem_wait((*P)->state.sem);
	sem_wait((*P)->state.sem);
	sem_wait((*P)[1].state.sem);
}

int			ft_process(t_parent *papa)
{
	int			i;
	pid_t		info;

	i = -1;
	dprintf(1, "nb  :%ld\n", papa->philo->number_philo);
	sem_unlink("/sem-mutex");
	if ((papa->philo[0].state.sem =
	sem_open("/sem-mutex", O_CREAT, 0660, papa->philo->number_philo)) == SEM_FAILED)
		return (free_all(papa->philo, "sem init failed\n"));
	sem_unlink("/sem-wmutex");
	if ((papa->philo[0].state.writesem =
	sem_open("/sem-wmutex", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (free_all(papa->philo, "sem init failed\n"));
	ft_mutex_global(&papa->philo);
	i = -1;
	while (++i < papa->philo->number_philo)
	{
		info = fork();
		if (info == -1)
			return (free_all(papa->philo, "fork init failed\n"));
		else if (info == 0) {
			papa->philo[i].state.child = info;
			job(&papa->philo[i]);
		}
	}
	if (info != 0)
	{
		int j = -1;
		int status;
		while (++j < papa->philo->number_philo){

    		waitpid(papa->philo[i].state.child, &status, 0);
    		printf("exit status %d = %d\n", i, WEXITSTATUS(status));
		}
	}
	return (ft_fini(papa));
}

int			main(int ac, char **av)
{
	t_parent *papa;

	if (!((ac == 5 || ac == 6) && ft_atoi(av[1]) > 0))
		return (write(1, "Error numbers arguments\n", 24));
	if (!(papa = (t_parent *)ft_calloc(1, sizeof(t_phil))))
		return (0);
	if (!(papa->philo = (t_phil *)ft_calloc(ft_atoi(av[1]) + 1, sizeof(t_phil))))
		return (0);
	if (!(ft_parse(ac, av, &papa->philo)))
		return (write(1, "Error arguments value\n", 22));
	return (ft_process(papa));
}
