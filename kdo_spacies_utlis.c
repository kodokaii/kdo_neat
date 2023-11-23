/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies_utlis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/22 13:54:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_reset_spacies(t_kdo_spacies *spacies)
{
	kdo_free_spacies(spacies);
	spacies->fitness_max = 0;
	spacies->fitness_avg = 0;
}

void	kdo_push_to_spacies(t_kdo_neat *nn,
		t_kdo_spacies *spacies, t_kdo_genome *genome)
{
	t_list	*genome_element;

	genome_element = ft_lstnew(genome);
	if (!genome_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	ft_lstadd_back(&spacies->genome, genome_element);
	spacies->genome_count++;
}

t_uint	kdo_spacies_fill_count(t_kdo_neat *nn)
{
	t_uint	i;

	i = 0;
	while (i < nn->population.spacies_count
		&& nn->population.spacies[i].genome_count)
		i++;
	return (i);
}
