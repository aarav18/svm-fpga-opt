#include "svm_pipeline.h"

void top_module(fixed_point_t input_feature[SVM_FEATURE_DIM],
                fixed_point_t support_vectors[SVM_SUPPORT_VECTOR_COUNT][SVM_FEATURE_DIM],
                fixed_point_t coefficients[SVM_SUPPORT_VECTOR_COUNT],
                fixed_point_t gamma,
                fixed_point_t &decision_result) {

#pragma HLS INTERFACE axis port=input_feature
#pragma HLS INTERFACE axis port=support_vectors
#pragma HLS INTERFACE axis port=coefficients
#pragma HLS INTERFACE s_axilite port=gamma
#pragma HLS INTERFACE axis port=decision_result
#pragma HLS INTERFACE ap_ctrl_none port=return

    svm_pipeline(input_feature, support_vectors, coefficients, gamma, decision_result);
}
