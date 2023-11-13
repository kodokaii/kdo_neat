/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/13 23:47:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KDO_NEAT_H
# define KDO_NEAT_H

# include "libft/libft.h"

# ifndef KDO_POPULATION_COUNT
#  define KDO_POPULATION_COUNT 100
# endif

# ifndef KDO_INPUT_COUNT
#  define KDO_INPUT_COUNT 2
# endif

# ifndef KDO_OUTPUT_COUNT
#  define KDO_OUTPUT_COUNT 2
# endif

struct			s_kdo_link;
struct			s_kdo_node;
typedef float	(*t_kdo_activation_func)(float in);

typedef enum e_node_type
{
	INPUT_NODE,
	HIDDEN_NODE,
	OUTPUT_NODE,
}	t_node_type;

typedef struct s_kdo_link
{
	struct s_kdo_node	*to;
	float				weight;
	t_bool				enable;
}	t_kdo_link;

typedef struct s_kdo_node
{
	t_list				*link;
	t_uint				link_count;
	float				input;
	float				bias;
	t_uint				activation_func;
	t_uint				layer;
	t_node_type			type;
	t_uint				id;
}	t_kdo_node;

typedef struct s_kdo_genome
{
	t_list	*node_list;
	t_bst	*node_sort;
	t_uint	node_count;
	t_uint	link_count;
	float	fitness;
	t_uint	id;
}	t_kdo_genome;

typedef struct s_kdo_genome_buf
{
	t_buf	link;
	t_buf	node;
	t_uint	link_count;
	t_uint	node_count;
}	t_kdo_genome_buf;

typedef struct s_kdo_spacies
{
	t_list	*genome;
	t_uint	genome_count;
	t_uint	no_progress_count;
	float	fitness_max;
	float	fitness_avg;
}	t_kdo_spacies;

typedef struct s_kdo_population
{
	t_kdo_genome		genome[KDO_POPULATION_COUNT];
	t_kdo_genome		old_genome[KDO_POPULATION_COUNT];
	t_kdo_genome_buf	genome_buf;
	t_kdo_genome_buf	old_genome_buf;
	t_buf				spacies;
	t_uint				spacies_count;
	t_uint				generation_count;
}	t_kdo_population;

typedef struct s_kdo_neat_params
{
	float	excess_coef;	
	float	disjoint_coef;
	float	weight_coef;
	float	diff_limit;
	float	diff_modifer;
	float	drop_off_age;
	float	survival_limit;
	float	mutate_link;
	float	mutate_weight_shift;
	float	mutate_weight_random;
	float	mutate_weight_toggle;
	float	mutate_node;
	float	mutate_bias;
	float	mutate_function;
}	t_kdo_neat_params;

typedef struct s_kdo_neat
{
	t_kdo_population	pop;
	t_kdo_neat_params	params;
	t_kdo_genome		best_genome;
	t_kdo_genome_buf	best_genome_buf;
}	t_kdo_neat;

float	kdo_identity(float in);
float	kdo_step(float in);
float	kdo_relu(float in);
float	kdo_softsign(float in);
float	kdo_sigmoid(float in);

#endif
