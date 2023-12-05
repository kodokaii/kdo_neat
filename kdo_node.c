/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 03:36:11 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_node_load(t_kdo_neat *nn, t_kdo_genome *genome_from)
{
	t_kdo_save_node	*node_src;
	t_kdo_node		*node_dst;
	t_uint			i;

	i = 0;
	node_src = nn->params.load->node + nn->params.load->node_index;
	node_dst = kdo_get_node(nn, node_src->layer, node_src->type, node_src->id);
	node_dst->bias = node_src->bias;
	node_dst->activation_index
		= node_src->activation_index % nn->params.activation_func_count;
	kdo_add_node(nn, genome_from, node_dst);
	nn->params.load->node_index++;
}

void	kdo_feed_forward_node(t_kdo_neat *nn, t_kdo_node *node)
{
	t_list	*current;

	node->output = (nn->params.activation_func[node->activation_index])
		(node->input + node->bias);
	current = node->link;
	while (current)
	{
		kdo_feed_forward_link(current->data, node->output);
		current = current->next;
	}
	node->input = 0;
}

void	kdo_crossover_node(t_kdo_node *node1, t_kdo_node *node2)
{
	t_list	*current1;
	t_list	*current2;
	int		cmp;

	current1 = node1->link;
	current2 = node2->link;
	while (current1 && current2)
	{
		cmp = kdo_link_id_cmp(current1->data, current2->data);
		if (cmp == 0)
			kdo_crossover_link(current1->data, current2->data);
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
	}
	if (ft_randf() < 0.5)
	{
		node1->bias = node2->bias;
		node1->activation_index = node2->activation_index;
	}
}

void	kdo_mutate_node(t_kdo_neat *nn, t_kdo_node *node)
{
	float	rng;

	rng = ft_randf();
	if (rng <= nn->params.weight_random_prob)
		node->bias = (ft_randf() * 2) - 1;
	else if (rng <= nn->params.weight_shift_prob)
		node->bias += ((ft_randf_norm() * 2) - 1)
			* nn->params.bias_shift_coef;
	if (ft_randf() <= nn->params.function_change_prob)
		node->activation_index = ft_rand() % nn->params.activation_func_count;
}

void	kdo_save_node(t_kdo_neat *nn, t_kdo_node *node_src)
{
	t_kdo_save_node	*node_dst;
	t_list			*current;

	node_dst = nn->params.save->node + nn->params.save->node_index;
	node_dst->link_count = node_src->link_count;
	node_dst->bias = node_src->bias;
	node_dst->activation_index = node_src->activation_index;
	node_dst->layer = node_src->layer;
	node_dst->type = node_src->type;
	node_dst->id = node_src->id;
	current = node_src->link;
	while (current)
	{
		kdo_save_link(nn, current->data);
		current = current->next;
	}
	nn->params.save->node_index++;
}
