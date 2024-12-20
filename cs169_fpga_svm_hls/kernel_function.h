#ifndef KERNEL_FUNCTION_H
#define KERNEL_FUNCTION_H

#include "svm_data_type.h"
#include <hls_math.h>

// Function to compute RBF kernel value
fixed_point_t kernel_function(fixed_point_t gamma, fixed_point_t x, fixed_point_t v);

#endif // KERNEL_FUNCTION_H
