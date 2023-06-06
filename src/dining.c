/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:30:05 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 11:24:13 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_one_philo(t_philo *philo)
{
	if (philo->env->nbr_philos == 1)
	{
		pthread_mutex_unlock(philo->fork_left);
		ft_usleep(philo->env->time_to_die);
		print_ms_p(philo, "\033[1;33mDIED\033[0m");
		pthread_mutex_lock(philo->env->print_msg);
		philo->env->someone_died = 1;
		pthread_mutex_unlock(philo->env->print_msg);
		return (0);
	}
	return (1);
}

int	grabbing_forks_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->env->print_msg);
	if (philo->env->someone_died || philo->env->finish_dinner)
		return (0);
	pthread_mutex_unlock(philo->env->print_msg);
	print_ms_p(philo, "grabbed fork");
	if (!check_one_philo(philo))
		return (0);
	pthread_mutex_lock(philo->fork_right);
	print_ms_p(philo, "grabbed fork");
	pthread_mutex_lock(philo->env->print_msg);
	if (philo->env->someone_died || philo->env->finish_dinner)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->env->print_msg);
		return (0);
	}
	philo->times_eaten++;
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->env->print_msg);
	print_ms_p(philo, "is eating");
	ft_usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	return (1);
}

int	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->env->print_msg);
	if (philo->env->someone_died || philo->env->finish_dinner)
		return (0);
	pthread_mutex_unlock(philo->env->print_msg);
	print_ms_p(philo, "is sleeping");
	ft_usleep(philo->env->time_to_sleep);
	pthread_mutex_lock(philo->env->print_msg);
	if (philo->env->someone_died || philo->env->finish_dinner)
		return (0);
	pthread_mutex_unlock(philo->env->print_msg);
	print_ms_p(philo, "is thinking");
	return (1);
}

int	philo_ations(t_philo *philo)
{
	// if (is_starved(philo))
	// 	return (0);
	pthread_mutex_lock(philo->env->print_msg);
	if (philo->env->someone_died || philo->env->finish_dinner)
		return (0);
	pthread_mutex_unlock(philo->env->print_msg);
	if (!grabbing_forks_eating(philo))
		return (0);
	pthread_mutex_lock(philo->env->print_msg);
	if (philo->env->someone_died || philo->env->finish_dinner)
		return (0);
	pthread_mutex_unlock(philo->env->print_msg);
	// if (is_starved(philo))
	// 	return (0);
	if (!sleep_and_think(philo))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_msg);
	pthread_mutex_unlock(philo->print_msg);
	if ((philo->id % 2) == 0)
		usleep(200);
	pthread_mutex_lock(philo->print_msg);
	while (!philo->env->someone_died && !philo->env->finish_dinner)
	{
		pthread_mutex_unlock(philo->print_msg);
		if (philo_ations(philo) == 0)
			break ;
		pthread_mutex_lock(philo->print_msg);
	}
	pthread_mutex_unlock(philo->print_msg);
	return (NULL);
}
