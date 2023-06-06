/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 03:59:40 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 09:47:58 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_starved(t_philo *philo)
{
	unsigned long	diff_from_last_meal;

	pthread_mutex_lock(philo->env->print_msg);
	diff_from_last_meal = ft_get_time() - philo->last_meal;
	if (diff_from_last_meal > (unsigned long)philo->env->time_to_die)
	{
		philo->env->someone_died = 1;
		pthread_mutex_unlock(philo->env->print_msg);
		print_ms_p(philo, "\033[1;33mDIED\033[0m");
		return (1);
	}
	pthread_mutex_unlock(philo->env->print_msg);
	return (0);
}

void	ft_usleep(int time)
{
	usleep(time * 1000);
}

void	print_ms_p(t_philo *p, char *str)
{
	unsigned long	time;

	time = ft_get_time() - p->env->start_time;
	pthread_mutex_lock(p->print_msg);
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

void	ft_finish_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr_philos)
		pthread_join(env->philos_threads[i], NULL);
	i = -1;
	while (++i < env->nbr_philos)
	{	
		pthread_mutex_destroy(env->forks + i);
		pthread_mutex_destroy(env->print_msg + i);
		pthread_mutex_destroy(env->shield_mtx + i);
	}
}
