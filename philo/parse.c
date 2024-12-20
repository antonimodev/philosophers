/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:53 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/17 14:24:18 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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

bool	init_params(t_params *params, int ac, char **av)
{
	unsigned int	*values;

	values = parse_values(ac, av);
	if (!check_av(av, is_number) || !values[0])
		return (false);
	else
	{
		params->philos_num = values[0];
		params->time_to_die = values[1];
		params->time_to_eat = values[2];
		params->time_to_sleep = values[3];
		if (ac == 5)
			params->eat_times = values[4];
	}
	return(true);
}

unsigned int	*parse_values(int ac, char **av)
{
	unsigned int	*values;
	int				i;

	values = malloc(ac * sizeof(unsigned int));
	// proteger malloc, cuidao con lo que devuelve la funsion
	i = 0;
	while(av)
	{
		values[i] = ft_atoi(av[i]);
		if (!values[i])
		{
			printf("Error: parse_values: Values cannot be 0\n");
			memset(values, 0, ac * sizeof(unsigned int));
			return (values);
		}
		i++;
		av++;
	}
	return (values);
}
