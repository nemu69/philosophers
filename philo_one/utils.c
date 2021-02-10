/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nepage-l <nepage-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:51:39 by nepage-l          #+#    #+#             */
/*   Updated: 2021/02/10 15:47:09 by nepage-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long long	current_timestamp(t_phil *philo)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec * 1000LL + te.tv_usec / 1000)
	- philo->state.start_time;
	return (milliseconds);
}

void		ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void		ft_putnbr(long int n)
{
	int		div;
	int		mod;
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = n / -1;
	}
	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		div = n / 10;
		mod = n % 10;
		ft_putnbr(div);
		ft_putnbr(mod);
	}
}

void		ft_bzero(void *s, size_t n)
{
	size_t			i;
	char			*ptr;

	ptr = (char	*)s;
	i = 0;
	while (i != n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void		*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size * count)))
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
