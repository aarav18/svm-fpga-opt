#include "svm_data_type.h"
#include "svm_classifier.h"
#include "SV.h"
#include "alpha.h"

#define MULT_LUT_NUM 0

void svm_classifier(data_t in[DIMENSION], bool *out)
{
#pragma HLS DATAFLOW
#pragma HLS ARRAY_RESHAPE variable=in cyclic factor=16 dim=1  //For Dimension
#pragma HLS ARRAY_PARTITION variable=SVs cyclic factor=9 dim=1  //For Channel
#pragma HLS ARRAY_RESHAPE variable=SVs cyclic factor=16 dim=2  //For Dimension
#pragma HLS ARRAY_PARTITION variable=alpha cyclic factor=9 dim=1  //For Channel
#pragma HLS INTERFACE s_axilite port=out
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=in

    data18_10t sum = 0, ch_sums[9] = {0,0,0,0,0,0,0,0,0};
    data13_4t s_in[DIMENSION];
    for (int i = 0; i < DIMENSION; i++) {
        #pragma HLS UNROLL
        s_in[i] = in[i];
    }

#pragma HLS ARRAY_PARTITION variable=ch_sums cyclic factor=9 dim=1  //For Channel
    Sum_loop: for (int i = 0; i < ALPHA_NUM; i++)
    {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=9  //For Channel

        data8_3t parameter_k;
        getKernel(SVs[i], s_in, &parameter_k);

        data18_10t temp = parameter_k * alpha[i];
        #pragma HLS RESOURCE variable=temp core=Mul_LUT

        ch_sums[i % CH_NUM] += temp;
    }

    Channel_Sum_loop: for(int i = 0; i < CH_NUM; i++)
    {
#pragma HLS PIPELINE
#pragma HLS UNROLL
        sum += ch_sums[i];
    }

    *out = (sum + bias).is_neg();
}
