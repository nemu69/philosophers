/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:36:49 by nepage-l          #+#    #+#             */
/*   Updated: 2021/04/17 18:33:13 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_eat(t_phil *philo)
{
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " has taken a fork\n")))
		return (0);
	slock(philo, 1, 0);
	if (!(ft_statenow(P, " has taken a fork\n")))
		return (0);
	P->must_eat--;
	P->must_eat == -1 ? slock(P, 1, 1) : 0;
	if (!(ft_statenow(P, " is eating\n")))
		return (0);
	usleep(1000 * P->time_to_eat);
	slock(philo, 0, 0);
	slock(philo, 0, 0);
	last_graille(P);
	return (ft_sleep(philo));
}

int		ft_think(t_phil *philo)
{
	if (!(ft_statenow(P, " is thinking\n")))
		return (0);
	return (1);
}

int		ft_sleep(t_phil *philo)
{
	if (!(ft_statenow(P, " is sleeping\n")))
		return (0);
	usleep(1000 * P->time_to_sleep);
	return (ft_think(philo));
}

int		ft_status(t_parent *papa)
{
	int		status;
	int		i;
	pid_t	tmp_pid;

	status = 0;
	tmp_pid = -1;
	while (!status && tmp_pid <= 0)
		tmp_pid = waitpid(-1, &status, 0);
	i = -1;
	while (++i < papa->philo->number_philo)
		kill(papa->philo[i].state.child, SIGKILL);
	if (WEXITSTATUS(status))
		return (free_all(papa->P, NULL));
	return (free_all(papa->P, "Philo is bien graille\n"));
}

int		slock(t_phil *philo, int code, int nbmut)
{
	if (nbmut)
		code ? sem_wait(P->state.writesem) :
			sem_post(P->state.writesem);
	if (!nbmut)
		code ? sem_wait(P->state.sem) :
			sem_post(P->state.sem);
	return (0);
}
