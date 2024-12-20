#include "testData.h"
#include "svm_classifier.h"
#include "svm_data_type.h"
#include <math.h>
#include <iostream>
#define DATA_NUM 2000
#define PRED_ERROR 170
#define DIMENSION 16
#define HW_COSIM

int main(void)
{
    bool output = false;
    bool *op;
    int err_cnt = 0;
    bool op_buffer[DATA_NUM] = {0};
    op = &output;

#ifdef HW_COSIM
    // Run the SVM classifier on the data
    for (int i = 0; i < DATA_NUM; i++)
    {
        svm_classifier(&testData[DIMENSION * i], op);
        op_buffer[i] = *op;
    }
#endif

#ifdef HW_COSIM
    for (int i = 0; i < DATA_NUM; i++)
    {
        // Check HW result against SW
        if (op_buffer[i] != testDataLabel[i]) {
            err_cnt += 1;
        }
    }
#else
    // Just for testing without hardware cosimulation
    // std::cout << *op;
#endif

#ifdef HW_COSIM
    if (err_cnt != PRED_ERROR)
        std::cout << "ERROR: " << (float)err_cnt / 20.0 << "% mismatches detected!" << std::endl
                  << "Expected mismatches: " << PRED_ERROR / 20.0 << "%." << std::endl;
    else
        std::cout << "Test passes." << std::endl;
#endif

    return (err_cnt - PRED_ERROR);
}
