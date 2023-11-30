/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_layer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/30 13:59:49 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_layer_propagation(t_kdo_link *link, t_uint layer)
{
	t_list	*current;

	if (link->to->layer < layer + 1)
	{
		link->to->layer = layer + 1;
		current = link->to->link;
		while (current)
		{
			kdo_layer_propagation(current->data, layer + 1);
			current = current->next;
		}
	}
}
