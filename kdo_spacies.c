/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 22:42:27 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

float	_fitness_sum(t_kdo_neat *nn, t_kdo_spacies *spacies)
{
	t_list	*current;
	t_uint	parent_count;
	float	fitness_sum;

	fitness_sum = 0.0f;
	parent_count = (float)spacies->genome_count
		* nn->params.survival_limit + 1.0f;
	current = spacies->genome;
	while (current && parent_count--)
	{
		fitness_sum += ((t_kdo_genome *)current->data)->fitness;
		current = current->next;
	}
	return (fitness_sum);
}

t_kdo_genome	*_get_parent(t_kdo_spacies *spacies, float fitness_sum)
{
	t_list	*current;
	float	random_fitness;
	float	current_fitness_sum;

	random_fitness = fitness_sum * ft_randf();
	current = spacies->genome;
	current_fitness_sum = ((t_kdo_genome *)current->data)->fitness;
	while (current_fitness_sum < random_fitness)
	{
		current = current->next;
		current_fitness_sum += ((t_kdo_genome *)current->data)->fitness;
	}
	return (current->data);
}

void	kdo_crossover_spacies(t_kdo_neat *nn,
			t_kdo_spacies *spacies_dst, t_kdo_spacies *spacies_src)
{
	t_uint			child_count;
	t_kdo_genome	*parent1;
	t_kdo_genome	*parent2;
	float			fitness_sum;

	child_count = (t_uint)
		((spacies_src->fitness_avg / nn->old_population.fitness_avg)
			* (float)nn->params.genome_target_count + 1.0f);
	if (nn->params.genome_target_count
		< nn->population.genome_count + child_count)
		child_count
			= nn->params.genome_target_count - nn->population.genome_count;
	fitness_sum = _fitness_sum(nn, spacies_src);
	while (child_count--)
	{
		parent1 = kdo_get_genome(nn);
		kdo_dup_genome(nn, parent1, _get_parent(spacies_src, fitness_sum));
		parent2 = _get_parent(spacies_src, fitness_sum);
		kdo_crossover_genome(parent1, parent2);
		kdo_push_to_spacies(nn, spacies_dst, parent1);
	}
	spacies_dst->no_progress_count = spacies_src->no_progress_count;
}
