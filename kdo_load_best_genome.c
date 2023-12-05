/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_load_best_genome.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 13:40:07 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static int	_init(t_kdo_save_neat *save, t_kdo_neat *nn,
		t_kdo_activation_func *activation_func, t_uint activation_func_count)
{
	ft_bzero(nn, sizeof(t_kdo_neat));
	nn->params.genome_target_count = 1;
	nn->params.input_count = save->population.input_count;
	nn->params.output_count = save->population.output_count;
	nn->params.activation_func = activation_func;
	nn->params.activation_func_count = activation_func_count;
	nn->params.load = save;
	if (kdo_population_alloc(nn, &nn->population))
		return (EXIT_FAILURE);
	nn->input = malloc(nn->params.input_count * sizeof(float));
	if (!nn->input)
		return (EXIT_FAILURE);
	nn->output = malloc(nn->params.output_count * sizeof(float));
	if (!nn->output)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	_find_best_genome(t_kdo_neat *nn)
{
	t_uint	genome_index;
	t_uint	node_index;
	t_uint	link_index;
	float	best_fitness;

	best_fitness = 0.0f;
	link_index = 0;
	node_index = 0;
	genome_index = 0;
	while (genome_index < nn->params.load->population.genome_count)
	{
		if (best_fitness < nn->params.load->genome[genome_index].fitness)
		{
			best_fitness = nn->params.load->genome[genome_index].fitness;
			nn->params.load->genome_index = genome_index;
			nn->params.load->node_index = node_index;
			nn->params.load->link_index = link_index;
		}
		node_index += nn->params.load->genome[genome_index].node_count;
		link_index += nn->params.load->genome[genome_index].link_count;
		genome_index++;
	}
}

t_kdo_neat	kdo_load_best_genome(t_kdo_save_neat *save,
		t_kdo_activation_func *activation_func, t_uint activation_func_count)
{
	t_kdo_genome	*best_genome;	
	t_kdo_neat		nn;

	if (_init(save, &nn, activation_func, activation_func_count))
		kdo_neat_cleanup(&nn, ERRLOC, EXIT_FAILURE);
	_find_best_genome(&nn);
	best_genome = kdo_get_genome(&nn);
	if (!best_genome)
		kdo_neat_cleanup(&nn, "Get genome Failed", EXIT_FAILURE);
	kdo_genome_load(&nn, best_genome);
	return (nn);
}
