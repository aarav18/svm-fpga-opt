#ifndef SVM_PIPELINE_H
#define SVM_PIPELINE_H

#include "svm_data_type.h"

void svm_pipeline(fixed_point_t input_feature[SVM_FEATURE_DIM],
                  fixed_point_t support_vectors[SVM_SUPPORT_VECTOR_COUNT][SVM_FEATURE_DIM],
                  fixed_point_t coefficients[SVM_SUPPORT_VECTOR_COUNT],
                  fixed_point_t gamma,
                  fixed_point_t &decision_result);

#endif // SVM_PIPELINE_H
