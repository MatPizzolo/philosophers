#include "../philo.h"

#include <time.h>

void *philosopher(void *arg)
{
    unsigned long long time;
    t_philo philo_struct;
    t_map vars;
    struct timeval tv;
    pthread_mutex_t *mutex;  // Mutex pointer passed as an argument

    vars = *(t_map *)arg;
    start_philo_vars(vars.number_of_philos, &philo_struct);
    gettimeofday(&tv, NULL);
    time = (unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000;
    mutex = vars.mutex;

    pthread_mutex_lock(mutex);
    printf("%llu, philo %i is eating\n", time - vars.start_time_ms, philo_struct.id);
    pthread_mutex_unlock(mutex);

    struct timespec ts;
    ts.tv_sec = vars.time_to_eat / 1000;
    ts.tv_nsec = (vars.time_to_eat % 1000) * 1000000;
    nanosleep(&ts, NULL);

    return arg;
}



void	starting_philos(t_map start_vars)
{
	pthread_t		philo_t[start_vars.number_of_philos];
	pthread_mutex_t	mutex;
	int				i;
	
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < start_vars.number_of_philos)
	{
		start_vars.mutex = &mutex;
		if (pthread_create(philo_t + i, NULL, philosopher, &start_vars) != 0)
		{
			printf("Failed to create philo thread\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < start_vars.number_of_philos)
	{
		if (pthread_join(philo_t[i], NULL) != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
		i++;
	}
	pthread_mutex_destroy(&mutex);
}

// TODO - un struct tiene que tener un array a los structs de los philos
// los phios tienen que poder tomar datos del struct t_map (cambiarle de nombre a algo como t_env)
// t_env tiene que tener un array the mutex ppara los forks
// tengo que hacer un while, haciendo ell pthread_create pasandole como parametro mi t_env->philos[i]  y la funcion a pasar seria la rutina que tienen que cumplir


int	main(int argc, char	*argv[])
{
	t_map	start_vars;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments"), 1);
	starting_vars(argv, &start_vars);
	printf("start time: %d\n", start_vars.start_time_ms);
	starting_philos(start_vars);
	return (0);
}

