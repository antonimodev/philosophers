/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:17:00 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/08 12:40:04 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int ft_atoi(char *str)
{
	unsigned long res;
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
		if (!uint_limits(res))
			return (0);
	}
	return (sign * res);
}

bool	uint_limits(unsigned long num)
{
	if (num > UINT_MAX)
	{
		printf("Error: uint_limits: Your number is out of unsigned int limits\n");
		return (false);
	}
	return (true);
}

bool	is_number(void *param)
{
	char	*str;

	str = (char *)param;
	if (!*str)
	{
		printf("Error: is_number: Params must be numbers only!\n");
		return (false);
	}
    while (*str)
    {
        if (*str < '0' || *str > '9')
        {
			printf("Error: is_number: Params must be positives numbers only!\n");
			return (false);
		}
        str++;
    }
	return(true);
}
