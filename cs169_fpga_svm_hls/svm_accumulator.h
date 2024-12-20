#ifndef SVM_ACCUMULATOR_H
#define SVM_ACCUMULATOR_H

#include "svm_data_type.h"

// Function to accumulate weighted kernel outputs
fixed_point_t svm_accumulate(fixed_point_t kernel_output, fixed_point_t coefficient, fixed_point_t &result);

#endif // SVM_ACCUMULATOR_H
