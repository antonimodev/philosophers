/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/23 11:00:20 by antonimo         ###   ########.fr       */
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

unsigned int	*parse_values(int ac, char **av)
{
	unsigned int	*values;
	int				i;

	values = malloc(ac * sizeof(unsigned int));
	if (!values)
		return (NULL);
	i = 0;
	while (i < ac)
	{
		values[i] = ft_atoi(av[i]);
		if (!values[i])
		{
			printf("Error: parse_values: Values cannot be 0\n");
			memset(values, 0, ac * sizeof(unsigned int));
			return (values);
		}
		i++;
	}
	return (values);
}
