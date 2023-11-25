/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/25 01:54:35 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

float	kdo_identity(float in)
{
	return (in);
}

float	kdo_step(float in)
{
	if (0.0f < in)
		return (1.0f);
	return (0.0f);
}

float	kdo_relu(float in)
{
	if (0.0f < in)
		return (in);
	return (0.0f);
}

float	kdo_softsign(float in)
{
	return (in / (1.0f + ft_abs_float(in)));
}

float	kdo_sigmoid(float in)
{
	return (1.0f / (1.0f + ft_expf(-in)));
}
