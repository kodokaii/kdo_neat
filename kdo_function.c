/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/13 03:07:11 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

float	kdo_identity(float in)
{
	return (in);
}

float	kdo_step(float in)
{
	if (0 < in)
		return (1);
	return (0);
}

float	kdo_relu(float in)
{
	if (0 < in)
		return (in);
	return (0);
}

float	kdo_softsign(float in)
{
	return (in / (1 + ft_abs_float(in)));
}

float	kdo_sigmoid(float in)
{
	return (1 / (1 + ft_expf(-in)));
}
