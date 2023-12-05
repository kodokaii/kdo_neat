/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 13:27:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_init(t_kdo_neat *nn, t_kdo_neat_params *params)
{
	ft_bzero(nn, sizeof(t_kdo_neat));
	nn->params = *params;
	nn->input = malloc(params->input_count * sizeof(float));
	if (!nn->input)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	nn->output = malloc(params->output_count * sizeof(float));
	if (!nn->output)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	if (kdo_population_alloc(nn, &nn->population))
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	if (kdo_population_alloc(nn, &nn->old_population))
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	if (params->load)
	{
		if (params->load->population.input_count != params->input_count
			|| params->load->population.output_count != params->output_count)
			kdo_neat_cleanup(nn, "Load invalid", EXIT_FAILURE);
		kdo_population_load(nn);
	}
	else
		kdo_population_init(nn);
}
