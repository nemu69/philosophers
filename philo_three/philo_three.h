/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:27 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/10 15:42:16 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# define P philo

typedef struct		s_state
{
	int				nb;
	int				eating;
	int				forkr;
	pid_t			child;
	sem_t			*sem;
	sem_t			*writesem;
	long long		start_time;
	long long		last_eat;
}					t_state;

typedef	struct		s_phil
{
	long			number_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			ac;
	int				err;
	t_state			state;
}					t_phil;

typedef	struct		s_parent
{
	t_phil			*philo;
	pid_t			dad;
}					t_parent;

int					slock(t_phil *philo, int code, int nbmut);
int					free_all(t_phil *philo, char *str);
int					check_death(t_phil *philo);
int					ft_statenow(t_phil *philo, char *str);
int					ft_death(t_phil *philo, long long time);
int					ft_parse(int ac, char **av, t_phil **philo);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
long long			current_timestamp(t_phil *philo);
void				ft_putnbr(long int n);
void				ft_putstr(char *s);
void				last_graille(t_phil *philo);
int					ft_eat(t_phil *philo);
int					ft_think(t_phil *philo);
int					ft_sleep(t_phil *philo);
int					ft_must_eat(t_phil *philo);

#endif
