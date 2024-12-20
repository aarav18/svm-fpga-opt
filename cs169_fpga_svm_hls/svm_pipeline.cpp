#include "svm_pipeline.h"
#include "kernel_function.h"
#include "svm_accumulator.h"

void svm_pipeline(fixed_point_t input_feature[SVM_FEATURE_DIM],
                  fixed_point_t support_vectors[SVM_SUPPORT_VECTOR_COUNT][SVM_FEATURE_DIM],
                  fixed_point_t coefficients[SVM_SUPPORT_VECTOR_COUNT],
                  fixed_point_t gamma,
                  fixed_point_t &decision_result) {

#pragma HLS PIPELINE
    fixed_point_t result = 0;

    // Loop through each support vector
    for (int i = 0; i < SVM_SUPPORT_VECTOR_COUNT; i++) {
#pragma HLS UNROLL factor=4
        fixed_point_t partial_sum = 0;

        // Compute RBF kernel for each feature
        for (int j = 0; j < SVM_FEATURE_DIM; j++) {
#pragma HLS PIPELINE
            partial_sum += kernel_function(gamma, input_feature[j], support_vectors[i][j]);
        }

        // Accumulate the result
        svm_accumulate(partial_sum, coefficients[i], result);
    }

    decision_result = result;
}
