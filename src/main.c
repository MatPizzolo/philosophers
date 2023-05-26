#include "../philo.h"

void *routine(void *arg)
{
    int id;

    id = *(int *)arg;
	printf("Routine del %i\n", id);

    return arg;
}



void	starting_philos(t_env vars)
{
	int		i;
	int		nbr;
	int		*thread_arg;
	
	nbr = vars.nbr_philos;
	i = -1;
	while (++i < nbr)
	{   
		thread_arg = malloc(sizeof(int) * 1);
		*thread_arg = i;
		if (pthread_create(&vars.philos[i].philo, NULL, routine, thread_arg) != 0)
		{
			printf("Failed to create philo thread\n");
			return ;
		}
	}
	i = -1;
	while (++i < nbr)
	{
		if (pthread_join(vars.philos[i].philo, NULL) != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
	}
}


// los philos tienen que poder tomar datos del struct t_map (cambiarle de nombre a algo como t_env)
// t_env tiene que tener un array the mutex para los forks


int	main(int argc, char	*argv[])
{
	t_env	start_vars;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments"), 1);
	starting_vars(argv, &start_vars);
	start_vars.philos = (t_philo *)malloc(start_vars.nbr_philos * sizeof(t_philo));
	i = -1;
	while (++i < start_vars.nbr_philos)
		start_philo_vars(i, start_vars.philos + i);
	starting_philos(start_vars);
	return (0);
}

