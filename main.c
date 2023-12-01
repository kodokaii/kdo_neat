/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 20:05:41 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_get_prob(t_kdo_neat_params *params)
{
	params->link_coef = 2.0f;
	params->node_coef = 3.0f;
	params->weight_coef = 1.0f;
	params->bias_coef = 1.5f;
	params->compatibility_limit = 6.0f;
	params->compatibility_modifer = 0.3f;
	params->dropoff_age = 15.0f;
	params->survival_limit = 0.2f;
	params->mutate_link_prob = 1.0f;
	params->weight_shift_prob = 0.9f;
	params->weight_random_prob = 0.1f;
	params->link_toggle_prob = 0.02f;
	params->link_add_prob = 0.01f;
	params->mutate_node_prob = 0.9f;
	params->bias_shift_prob = 0.5f;
	params->function_change_prob = 0.1f;
	params->node_add_prob = 0.005f;
}

float	kdo_xor(t_kdo_neat *nn, t_uint genome_being, void *ptr)
{
	float			diff;
	float			output;
	static float	input[4][2]
		= {{0, 0}, {1, 0}, {0, 1}, {1, 1}};

	diff = 0;
	(void)ptr;
	kdo_set_input(nn, input[0]);
	output = *kdo_feed_forward(nn, genome_being);
	diff += ft_abs_double(0.0f - output);
	kdo_set_input(nn, input[1]);
	output = *kdo_feed_forward(nn, genome_being);
	diff += ft_abs_double(1.0f - output);
	kdo_set_input(nn, input[2]);
	output = *kdo_feed_forward(nn, genome_being);
	diff += ft_abs_double(1.0f - output);
	kdo_set_input(nn, input[3]);
	output = *kdo_feed_forward(nn, genome_being);
	diff += ft_abs_double(0.0f - output);
	return (1 / ft_max_double(diff, 0.0001));
}

int	main(void)
{
	t_kdo_neat_params				params;
	static t_kdo_activation_func	func[5]
		= {kdo_sigmoid, kdo_softsign, kdo_relu, kdo_step, kdo_identity};

	_get_prob(&params);
	params.fitness_target = 1000.0f;
	params.species_target_count = 10;
	params.genome_target_count = 1000;
	params.input_count = 2;
	params.output_count = 1;
	params.fitness_func = &kdo_xor;
	params.activation_func = func;
	params.activation_func_count = 5;
	params.ptr = NULL;
	kdo_neat(&params);
	return (0);
}
