/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 03:59:40 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 16:49:18 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_starved(t_philo *philo)
{
	unsigned long	diff_from_last_meal;

	pthread_mutex_lock(philo->env->times_eat_mtx);
	diff_from_last_meal = ft_get_time() - philo->last_meal;
	if (diff_from_last_meal > (unsigned long)philo->env->time_to_die)
	{
		pthread_mutex_unlock(philo->env->times_eat_mtx);
		pthread_mutex_lock(philo->env->check_death);
		philo->env->someone_died = 1;
		print_ms_death(philo);
		pthread_mutex_unlock(philo->env->check_death);
		pthread_mutex_unlock(philo->env->times_eat_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->env->check_death);
	pthread_mutex_unlock(philo->env->times_eat_mtx);
	return (0);
}

void	ft_usleep(int time)
{
	unsigned long	reference;

	reference = time + ft_get_time();
	while (ft_get_time() < reference)
		usleep(700);
}

void	print_ms_death(t_philo *p)
{
	unsigned long	time;

	time = ft_get_time() - p->env->start_time;
	pthread_mutex_lock(p->print_msg);
	if (p->env->can_print)
	{
		printf("%lu - %i, ", time, p->id);
		printf("\033[31;3m 💀 DIED 💀 \033[0m\n");
	}
	pthread_mutex_unlock(p->print_msg);
}

void	print_ms_p(t_philo *p, char *str)
{
	unsigned long	time;

	time = ft_get_time() - p->env->start_time;
	pthread_mutex_lock(p->print_msg);
	if (p->env->can_print)
		printf("%lu - %i, %s\n", time, p->id, str);
	pthread_mutex_unlock(p->print_msg);
}

unsigned long	ft_get_time(void)
{
	unsigned long	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (unsigned long)tv.tv_sec * 1000
		+ (unsigned long)tv.tv_usec / 1000;
	return (time);
}
