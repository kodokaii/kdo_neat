/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/23 22:55:07 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_feed_forward_node(t_kdo_neat *nn, t_kdo_node *node)
{
	t_list	*current;

	node->output = (nn->activation_func[node->activation_index])
		(node->input + node->bias);
	current = node->link;
	while (current)
	{
		kdo_feed_forward_link(current->data, node->output);
		current = current->next;
	}
	node->input = 0;
}

void	kdo_crossover_node(t_kdo_node *node1, t_kdo_node *node2,
			t_kdo_node *node_child)
{
	
}

void	kdo_mutate_node(t_kdo_neat *nn, t_kdo_node *node)
{
	float	rng;

	rng = ft_randf();
	if (rng <= nn->params.function_change_prob)
		node->activation_index = ft_rand() % nn->activation_func_count;
	if (rng <= nn->params.weight_random_prob)
		node->bias = (ft_randf() * 2) - 1;
	else if (rng <= nn->params.weight_shift_prob)
		node->bias += ((ft_randf_norm() * 2) - 1) / 10;
}
