/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_genome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/23 22:58:53 by nlaerema         ###   ########.fr       */
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
	current = genome->node;
	ft_lstsort(&genome->node, kdo_node_layer_cmp);
	while (current)
	{
		if (((t_kdo_node *)genome->node)->type == INPUT_NODE)
			((t_kdo_node *)genome->node)->input += nn->input[input_index++];
		kdo_feed_forward_node(nn, current->data);
		if (((t_kdo_node *)genome->node)->type == OUTPUT_NODE)
			((t_kdo_node *)genome->node)->input += nn->output[output_index++];
		current = current->next;
	}
}

void	kdo_mutate_genome(t_kdo_neat *nn, t_kdo_genome *genome)
{
	if (ft_randf() <= nn->params.mutate_link_prob)
		kdo_mutate_link(nn,
			kdo_get_random_link(kdo_get_random_node(genome)->data)->data);
	if (ft_randf() <= nn->params.link_add_prob)
		kdo_add_random_link(nn, genome);
	if (ft_randf() <= nn->params.mutate_node_prob)
		kdo_mutate_node(nn, kdo_get_random_node(genome)->data);
	if (ft_randf() <= nn->params.node_add_prob)
		kdo_add_random_node(nn, genome);
}
