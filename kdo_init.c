/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 00:53:08 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_init(t_kdo_neat *nn, t_kdo_neat_params *params)
{
	t_uint	i;

	i = 0;
	ft_bzero(nn, sizeof(t_kdo_neat));
	nn->params = *params;
	nn->input = malloc(params->input_count * sizeof(float));
	nn->output = malloc(params->output_count * sizeof(float));
	kdo_population_init(nn, &nn->population);
	kdo_population_alloc(nn, &nn->old_population);
	while (i < nn->population.genome_count)
	{
		kdo_push_to_species(nn, kdo_find_species(nn, nn->population.genome + i),
			nn->population.genome + i);
		i++;
	}
}
