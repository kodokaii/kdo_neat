/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_genome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 16:15:57 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_feed_forward_genome(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_list	*current;
	t_uint	input_index;
	t_uint	output_index;

	output_index = 0;
	input_index = 0;
	ft_lstsort(&genome->node, kdo_node_layer_cmp);
	current = genome->node;
	while (current)
	{
		if (((t_kdo_node *)current->data)->type == INPUT_NODE)
			((t_kdo_node *)current->data)->input += nn->input[input_index++];
		kdo_feed_forward_node(nn, current->data);
		if (((t_kdo_node *)current->data)->type == OUTPUT_NODE)
			nn->output[output_index++] = ((t_kdo_node *)current->data)->output;
		current = current->next;
	}
}

void	kdo_crossover_genome(t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_list	*current1;
	t_list	*current2;
	int		cmp;

	ft_lstsort(&genome1->node, &kdo_node_id_cmp);
	ft_lstsort(&genome2->node, &kdo_node_id_cmp);
	current1 = genome1->node;
	current2 = genome2->node;
	while (current1 && current2)
	{
		cmp = kdo_node_id_cmp(current1->data, current2->data);
		if (cmp == 0)
			kdo_crossover_node(current1->data, current2->data);
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
	}
}

void	kdo_mutate_genome(t_kdo_neat *nn, t_kdo_genome *genome)
{
	if (ft_randf() <= nn->params.mutate_link_prob)
		kdo_mutate_link(nn,
			kdo_get_random_link(kdo_get_linked_node(genome)->data)->data);
	if (ft_randf() <= nn->params.link_add_prob)
		kdo_add_random_link(nn, genome);
	if (ft_randf() <= nn->params.mutate_node_prob)
		kdo_mutate_node(nn, kdo_get_random_node(genome)->data);
	if (ft_randf() <= nn->params.node_add_prob)
		kdo_add_random_node(nn, genome);
}