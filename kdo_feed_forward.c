/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_feed_forward.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/28 23:14:36 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_set_input(t_kdo_neat *nn, float *input)
{
	t_uint	i;

	i = 0;
	while (i < nn->params.input_count)
	{
		nn->input[i] = input[i];
		i++;
	}
}

float	*kdo_feed_forward(t_kdo_neat *nn, t_uint genome_being)
{
	if (genome_being < nn->population.genome_count)
	{
		kdo_feed_forward_genome(nn, nn->population.genome + genome_being);
		return (nn->output);
	}
	return (NULL);
}
