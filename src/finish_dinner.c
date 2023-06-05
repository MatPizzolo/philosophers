/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 06:21:53 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/05 10:06:17 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_starved(t_philo *philo)
{
	unsigned long	diff_from_last_meal;

	pthread_mutex_lock(philo->env->print_msg);
	diff_from_last_meal = ft_get_time() - philo->last_meal;
	// printf("dif %lu\n", diff_from_last_meal);
	// usleep(20000);
	if ((int)diff_from_last_meal > philo->env->time_to_die)
	{
		philo->env->someone_died = 1;
		pthread_mutex_unlock(philo->env->print_msg);
		print_ms_p(philo, "\033[1;33mDIED\033[0m");
		return (1);
	}
	pthread_mutex_unlock(philo->env->print_msg);
	return (0);
}

int	a_philo_is_starved(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr_philos)
	{
		if (is_starved(env->philos_struct[i]))
			return (1);	
	}
	return (0);
}

int	are_philos_full(t_env *env)
{
	int	i;
	int	philos_full;

	philos_full = 0;
	i = -1;
	while (++i < env->nbr_philos)
	{
		pthread_mutex_lock(env->print_msg);
		if (env->philos_struct[i]->times_eaten >= env->times_must_eat)
			philos_full++;
		pthread_mutex_unlock(env->print_msg);
		if (philos_full == env->nbr_philos)
		{
			if (is_starved(env->philos_struct[i]))
				return (1);
			pthread_mutex_lock(env->print_msg);
			env->finish_dinner = 1;
			pthread_mutex_unlock(env->print_msg);
			printf("All philos have eaten\n");
			return (1);
		}
	}
	return (0);
}

int	finish_dinner(t_env *env, int argc)
{
	int	x;

	x = 1;
	while (x)
	{
		if (argc == 6)
		{
			if (are_philos_full(env))
				x = 0;
		}
		if (a_philo_is_starved(env))
			x = 0;
		pthread_mutex_lock(env->print_msg);
		if (env->someone_died)
			x = 0;
		pthread_mutex_unlock(env->print_msg);
	}	
	ft_finish_threads(env);
	return (0);
}
