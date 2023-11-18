/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_layer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/17 13:14:55 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_layer_propagation_link(t_kdo_link *link, t_uint layer)
{
	link->to->layer = ft_max_uint(link->to->layer, layer + 1);
	kdo_layer_propagation_node(link->to);
}

void	kdo_layer_propagation_node(t_kdo_node *node)
{
	t_list	*current;

	current = node->link;
	while (current)
	{
		kdo_layer_propagation_link(current->content, node->layer);
		current = current->next;
	}
}
