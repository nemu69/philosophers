#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include "philo_two/philo_two.h"

void		*job(void *arg)
{
	t_phil *philo;

	P = arg;

        dprintf(1 , "nb  : %d 1wreturn : %d\n", philo->state.nb ,sem_wait(philo[0].state.sem));
        dprintf(1 , "preturn : %d" ,sem_post(philo[0].state.sem));
        dprintf(1 , "nb  : %d 1wreturn : %d\n", philo->state.nb ,sem_wait(philo[0].state.writesem));


        dprintf(1 , "preturn : %d" ,sem_post(philo[0].state.writesem));
        // dprintf(1 , "preturn : %d" ,sem_post(philo[1].state.sem));


        // sem_post(philo->state.sem);
        // sem_post(philo[1].state.sem);
        // sem_post(philo[2].state.sem);
        dprintf(1,"boboobo\n");

}

void		ft_mutex_global(t_phil **philo)
{
	int i;

	i = -1;
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
	if ((P[0].state.sem = sem_open("/sem-mutex", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (free_all(philo, "sem init failed\n"));
	if ((P[0].state.writesem = sem_open("/sem-wmutex", O_CREAT, 0660, 1)) == SEM_FAILED)
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