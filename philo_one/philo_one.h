/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/01/30 14:18:13 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct		s_mut
{
	int nb;
	pthread_mutex_t mutex;
}					t_mut;

typedef	struct		s_phil
{
	long			number_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_time_philo_must_eat;
	int				forkl;
	int				forkr;
	int				err;
	t_mut			data;
}					t_phil;

int					ft_parse(int ac, char **av, t_phil *philo);
#endif
