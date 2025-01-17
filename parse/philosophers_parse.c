/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 13:36:22 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_av(char **av, bool (*function)(void *))
{
    while (*av)
    {
        if (!function(*av))
			return (false);
        av++;
    }
	return (true);
}

bool	init_args(t_args *args, int ac, char **av)
{
	unsigned int	*values;

	memset(args, 0, sizeof(t_args)); // Inicializamos la estructura
	if (!check_av(av, is_number))
		return (false);
	values = parse_values(ac, av);
	if (!values[0])
	{
		free(values);
		return (false);
	}
	args->philos_num = values[0];
	args->time_to_die = values[1];
	args->time_to_eat = values[2];
	args->time_to_sleep = values[3];
	if (ac == 5)
		args->eat_times = values[4];
	free(values);
	return(true);
}

unsigned int	*parse_values(int ac, char **av)
{
	unsigned int	*values;
	int				i;

	values = malloc(ac * sizeof(unsigned int));
	if (!values)
		return (NULL);
	i = 0;
	while(i < ac)
	{
		values[i] = ft_atoi(av[i]);
		if (!values[i])
		{
			printf("Error: parse_values: Values cannot be 0\n");
			free(values);
			memset(values, 0, ac * sizeof(unsigned int));
			return (values);
		}
		i++;
	}
	return (values);
}
