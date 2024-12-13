/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:18:53 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/13 13:52:09 by antonimo         ###   ########.fr       */
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

bool	is_number(void *param)
{
	char *str;

	str = (char *)param;
    while (*str)
    {
        if (*str < '0' || *str > '9')
        {
			printf("Error: is_number: Params must be numbers only!\n");
			return (NULL);
		}
        str++;
    }
	return(true);
}

bool	init_params(t_params *params, char **av)
{
	if (!check_av(av, is_number))
		return (false);
	params->philos_num = ft_atoi(av[0]);
	params->eat_times = ft_atoi(av[1]);
	params->time_to_eat = ft_atoi(av[2]);
	params->time_to_sleep = ft_atoi(av[3]);
	params->time_to_die = ft_atoi(av[4]);
	return(true);
}

int ft_atoi(char *str)
{
	int res;
	int sign;

	if (!str)
		return (0);
	res = 0;
	sign = 1;
	while((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while(*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str -'0';
		str++;
	}
	return (sign * res);
}
