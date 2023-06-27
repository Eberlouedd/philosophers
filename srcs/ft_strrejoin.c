/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrejoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:35:55 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/27 18:47:56 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	d;
	int	i;

	d = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[d] = src[i];
		i++;
		d++;
	}
	dest[d] = '\0';
	return (dest);
}

int	ft_long_gen(int size, char **strs, char *sep, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (i < size)
	{
		count += ft_strlen(strs[i]);
		i++;
	}
	count += ft_strlen(sep) * (size - 1);
	return (count);
}

char	*ft_strrejoin(int size, char **strs, char *sep, int start)
{
	char	*res;
	int		i;

	if (start > size)
		start = 0;
	i = start;
	if (size == 0)
	{
		res = malloc(sizeof(char));
		res[0] = '\0';
		return (res);
	}
	res = malloc(sizeof(char) * (ft_long_gen(size, strs, sep, start) + 1));
	if (!res)
		return (NULL);
	*res = '\0';
	while (i < size)
	{
		res = ft_strcat(res, strs[i]);
		i++;
		if (i < size)
			res = ft_strcat(res, sep);
	}
	return (res);
}
