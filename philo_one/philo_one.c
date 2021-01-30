/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/01/30 14:45:10 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void * job(void *arg) {
	mutex_data *md = (mutex_data*) arg;
	pthread_t tid = pthread_self();
	while ((*md).data < INCREMENT_LIMIT) {
		// Vérouillage du mutex
		pthread_mutex_lock(&(*md).mutex);
		(*md).data++;
		// Dévérouillage du mutex
		pthread_mutex_unlock(&(*md).mutex);
		printf("thread [ %ld ] data [ %i ]\n", tid, (*md).data);
		// Pause l'exécution du thread pendant 1 seconde
		sleep(1);
	}
	printf("Fin du thread %ld\n", tid);
	pthread_exit(NULL);
}

action pthread[philo]
{
	fonction eat
	fonction eat
	fonction eat
}

int	main(int ac, char **av)
{
	t_phil philo;
	if (ac == 5 || ac == 6)
	{
		if (!(ft_parse(ac, av, &philo)))
			return (write(1, "Error arguments value", 22));
		pthread_t threads[philo.number_philo];
		// function pour action philo 
	}
	else
		write(1, "Error numbers arguments", 24);
	return (0);
}
