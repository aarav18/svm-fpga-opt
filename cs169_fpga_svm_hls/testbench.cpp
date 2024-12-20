#include "top_module.h"
#include <iostream>

int main() {
    fixed_point_t input_feature[SVM_FEATURE_DIM];
    fixed_point_t support_vectors[SVM_SUPPORT_VECTOR_COUNT][SVM_FEATURE_DIM];
    fixed_point_t coefficients[SVM_SUPPORT_VECTOR_COUNT];
    fixed_point_t gamma = 0.5;
    fixed_point_t decision_result;

    // Initialize test data
    for (int i = 0; i < SVM_FEATURE_DIM; i++) {
        input_feature[i] = i * 0.1;
    }

    for (int i = 0; i < SVM_SUPPORT_VECTOR_COUNT; i++) {
        for (int j = 0; j < SVM_FEATURE_DIM; j++) {
            support_vectors[i][j] = j * 0.1;
        }
        coefficients[i] = i * 0.01;
    }

    // Call the top module
    top_module(input_feature, support_vectors, coefficients, gamma, decision_result);

    std::cout << "Decision result: " << decision_result << std::endl;

    return 0;
}
