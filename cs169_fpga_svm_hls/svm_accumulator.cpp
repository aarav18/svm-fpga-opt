#include "svm_accumulator.h"

fixed_point_t svm_accumulate(fixed_point_t kernel_output, fixed_point_t coefficient, fixed_point_t &result) {
    result += kernel_output * coefficient;
    return result;
}
