#include "kernel_function.h"

fixed_point_t kernel_function(fixed_point_t gamma, fixed_point_t x, fixed_point_t v) {
    fixed_point_t diff = x - v;
    fixed_point_t dist = diff * diff; // Compute squared distance
    return hls::exp(-gamma * dist);  // RBF kernel using HLS exponential function
}
