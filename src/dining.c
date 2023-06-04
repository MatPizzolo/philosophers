/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:30:05 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/02 09:57:59 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_starved(t_philo *philo)
{
	unsigned long	diff_from_last_meal;

	// printf("get: %lu\n", ft_get_time());
	diff_from_last_meal = ft_get_time() - philo->last_meal;
	// printf("diff: %lu\to die %i\n", diff_from_last_meal, philo->env->time_to_die);
	if ((int)diff_from_last_meal > philo->env->time_to_die)
	{
		pthread_mutex_lock(philo->shield_mtx);
		philo->is_starved = 1;
		pthread_mutex_unlock(philo->shield_mtx);
		print_ms_p(philo, "\033[1;33mDIED\033[0m");
		return (1);
	}
	return (0);
}

int	philo_ations(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_ms_p(philo, "grabbed fork");
	pthread_mutex_lock(philo->fork_right);
	print_ms_p(philo, "grabbed fork");
	if (is_starved(philo) == 1)
		return (0);
	print_ms_p(philo, "is eating");
	philo->last_meal = ft_get_time() - philo->env->start_time;
	philo->times_eaten++;
	ft_usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	print_ms_p(philo, "is sleeping");
	usleep(philo->env->time_to_sleep);
	print_ms_p(philo, "is thinking");
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		check_death;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_msg);
	pthread_mutex_unlock(philo->print_msg);
	check_death = 1;
	if ((philo->id % 2) == 0)
		usleep(200);
	philo->last_meal = ft_get_time();
	while (1)
	{
		if (philo_ations(philo) == 0)
			break ;
	}
	print_ms_p(philo, "exited routine");
	return (NULL);
}

int	finish_dinner(t_env *env)
{
	int	i;
	int	x;

	x = 1;
	while (x)
	{
		i = -1;
		while (++i < env->nbr_philos && x)
		{
			pthread_mutex_lock(env->philos_struct[i]->shield_mtx);
			if (env->philos_struct[i]->is_starved == 1)
				x = 0;
			pthread_mutex_unlock(env->philos_struct[i]->shield_mtx);
		}
	}
	printf("WHYY\n");
	// printf("1");
	// pthread_mutex_lock(env->finish_dinner_mtx);
	// env->finish_dinner = 1;
	// pthread_mutex_unlock(env->finish_dinner_mtx);
	// printf("2\n");
	ft_finish_threads(env);
	return (0);
}
