/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:40 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/27 19:24:11 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_compte(const char *str, int i)
{
	int	compte;

	compte = 1;
	while (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		compte *= 10;
		i++;
	}
	return (compte);
}

static int	ret_sign(int signe, int nb)
{
	if (signe == '+')
		return (nb);
	else
		return (-nb);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		nb;
	char	signe;

	i = 0;
	signe = '+';
	nb = 0;
	while (nptr[i] < '0' || nptr[i] > '9')
	{
		if (nptr[i] == '-' || nptr[i] == '+')
		{
			signe = nptr[i];
			i++;
			break ;
		}
		else if ((nptr[i] < 9 || nptr[i] > 13) && nptr[i] != 32)
			return (0);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb += ((int)nptr[i] - 48) * ft_compte(nptr, i);
		i++;
	}
	return (ret_sign(signe, nb));
}
