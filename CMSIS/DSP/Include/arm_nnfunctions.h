/*
 * Copyright (C) 2010-2017 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* ----------------------------------------------------------------------
 * Project:      CMSIS NN Library
 * Title:        arm_nnfunctions.h
 * Description:  Public header file for CMSIS NN Library
 *
 * $Date:        13. November 2017
 * $Revision:    V.x.x.x
 *
 * Target Processor: Cortex-M4 and Cortex-M7 cores
 * -------------------------------------------------------------------- */

#ifndef _ARM_NNFUNCTIONS_H
#define _ARM_NNFUNCTIONS_H

#include "arm_nnsupportfunctions.h"

#define USE_INTRINSIC

#ifdef __cplusplus
extern    "C"
{
#endif

/**
 * @defgroup Conv Convolution Layer Functions
 *
 * Perform convolution layer
 *
 * The convolution is implemented in 2 steps: im2col and GEMM
 *
 * im2col is a process of converting each patch of image data into 
 * a column. After im2col, the convolution is computed as matrix-matrix
 * multiplication.
 * 
 * To reduce the memory footprint, the im2col is performed partially.
 * Each iteration, only a few column (i.e., patches) are generated and 
 * computed with GEMM kernels similar to CMSIS-DSP arm_mat_mult functions.
 *
 */

  /**
   * @brief Basic Q7 convolution function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       wt          pointer to kernel weights
   * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       bias        pointer to bias
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in,out]   Im_out      pointer to output tensor
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input, 
   * @param[in,out]   bufferB     pointer to buffer space for output
   * @return     The function returns <code>ARM_MATH_SUCCESS</code> 
   *
   */

    arm_status arm_convolve_HWC_q7_basic(const q7_t * Im_in,
                                         const uint16_t dim_im_in,
                                         const uint16_t ch_im_in,
                                         const q7_t * wt,
                                         const uint16_t ch_im_out,
                                         const uint16_t dim_kernel,
                                         const uint16_t padding,
                                         const uint16_t stride,
                                         const q7_t * bias,
                                         const uint16_t bias_shift,
                                         const uint16_t out_shift,
                                         q7_t * Im_out, 
                                         const uint16_t dim_im_out, 
                                         q15_t * bufferA, 
                                         q7_t * bufferB);

  /**
   * @brief Basic Q15 convolution function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       wt          pointer to kernel weights
   * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       bias        pointer to bias
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in,out]   Im_out      pointer to output tensor
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input, 
   * @param[in,out]   bufferB     pointer to buffer space for output
   * @return     The function returns <code>ARM_MATH_SUCCESS</code> 
   *
   */

    arm_status arm_convolve_HWC_q15_basic(const q15_t * Im_in,
                                          const uint16_t dim_im_in,
                                          const uint16_t ch_im_in,
                                          const q15_t * wt,
                                          const uint16_t ch_im_out,
                                          const uint16_t dim_kernel,
                                          const uint16_t padding,
                                          const uint16_t stride,
                                          const q15_t * bias,
                                          const uint16_t bias_shift,
                                          const uint16_t out_shift,
                                          q15_t * Im_out, 
                                          const uint16_t dim_im_out, 
                                          q15_t * bufferA, 
                                          q7_t * bufferB);

  /**
   * @brief Fast Q7 convolution function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       wt          pointer to kernel weights
   * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       bias        pointer to bias
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in,out]   Im_out      pointer to output tensor
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input, 
   * @param[in,out]   bufferB     pointer to buffer space for output
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   *
   * This function is the version with full list of optimization tricks, but with
   * some contraints:
   *   ch_im_in is multiple of 4
   *   ch_im_out is multiple of 2
   */

    arm_status arm_convolve_HWC_q7_fast(const q7_t * Im_in,
                                        const uint16_t dim_im_in,
                                        const uint16_t ch_im_in,
                                        const q7_t * wt,
                                        const uint16_t ch_im_out,
                                        const uint16_t dim_kernel,
                                        const uint16_t padding,
                                        const uint16_t stride,
                                        const q7_t * bias,
                                        const uint16_t bias_shift,
                                        const uint16_t out_shift,
                                        q7_t * Im_out, 
                                        const uint16_t dim_im_out, 
                                        q15_t * bufferA, 
                                        q7_t * bufferB);

  /**
   * @brief Q7 version of convolution for RGB image
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       wt          pointer to kernel weights
   * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       bias        pointer to bias
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in,out]   Im_out      pointer to output tensor
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input, 
   * @param[in,out]   bufferB     pointer to buffer space for output
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   *
   * This kernel is written exclusively for convolution with ch_im_in
   * equals 3. This applies on the first layer of CNNs which has input
   * image with RGB format.
   */

    arm_status arm_convolve_HWC_q7_RGB(const q7_t * Im_in,
                                       const uint16_t dim_im_in,
                                       const uint16_t ch_im_in,
                                       const q7_t * wt,
                                       const uint16_t ch_im_out,
                                       const uint16_t dim_kernel,
                                       const uint16_t padding,
                                       const uint16_t stride,
                                       const q7_t * bias,
                                       const uint16_t bias_shift,
                                       const uint16_t out_shift,
                                       q7_t * Im_out, 
                                       const uint16_t dim_im_out, 
                                       q15_t * bufferA, 
                                       q7_t * bufferB);

  /**
   * @brief Fast Q15 convolution function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       wt          pointer to kernel weights
   * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       bias        pointer to bias
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in,out]   Im_out      pointer to output tensor
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input, 
   * @param[in,out]   bufferB     pointer to buffer space for output
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   *
   * This function is the version with full list of optimization tricks, but with
   * some contraints:
   *   ch_im_in is multiple of 2
   *   ch_im_out is multiple of 2
   */

    arm_status arm_convolve_HWC_q15_fast(const q15_t * Im_in,
                                         const uint16_t dim_im_in,
                                         const uint16_t ch_im_in,
                                         const q15_t * wt,
                                         const uint16_t ch_im_out,
                                         const uint16_t dim_kernel,
                                         const uint16_t padding,
                                         const uint16_t stride,
                                         const q15_t * bias,
                                         const uint16_t bias_shift,
                                         const uint16_t out_shift,
                                         q15_t * Im_out, 
                                         const uint16_t dim_im_out, 
                                         q15_t * bufferA, 
                                         q7_t * bufferB);

  /**
   * @brief Q7 depthwise separable convolution function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       wt          pointer to kernel weights
   * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       bias        pointer to bias
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in,out]   Im_out      pointer to output tensor
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input, 
   * @param[in,out]   bufferB     pointer to buffer space for output
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   *
   * This function is the version with full list of optimization tricks, but with
   * some contraints:
   *   ch_im_in is multiple of 2
   *   ch_im_out is multiple of 2
   */

    arm_status arm_depthwise_separable_conv_HWC_q7(const q7_t * Im_in,
                                                   const uint16_t dim_im_in,
                                                   const uint16_t ch_im_in,
                                                   const q7_t * wt,
                                                   const uint16_t ch_im_out,
                                                   const uint16_t dim_kernel,
                                                   const uint16_t padding,
                                                   const uint16_t stride,
                                                   const q7_t * bias,
                                                   const uint16_t bias_shift,
                                                   const uint16_t out_shift,
                                                   q7_t * Im_out,
                                                   const uint16_t dim_im_out, 
                                                   q15_t * bufferA, 
                                                   q7_t * bufferB);

/**
 * @defgroup FC Fully-connected Layer Functions
 *
 * Perform fully-connected layer
 *
 * Fully-connected layer is basically a matrix-vector multiplication
 * with bias. The matrix is the weights and the input/output vectors
 * are the activation values. Supported {weight, activation} precisions
 * include {8-bit, 8-bit}, {16-bit, 16-bit}, and {8-bit, 16-bit}.
 *
 * Here we have two types of kernel functions. The basic function
 * implements the function using regular GEMV approach. The opt functions
 * operates with weights in interleaved formats. 
 *
 */

  /**
   * @brief Q7 basic fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>ARM_MATH_SUCCESS</code>
   *
   */

    arm_status arm_fully_connected_q7(const q7_t * pV,
                                      const q7_t * pM,
                                      const uint16_t dim_vec,
                                      const uint16_t num_of_rows,
                                      const uint16_t bias_shift,
                                      const uint16_t out_shift, 
                                      const q7_t * bias, 
                                      q7_t * pOut, 
                                      q15_t * vec_buffer);

  /**
   * @brief Q7 opt fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>ARM_MATH_SUCCESS</code>
   *
   */

    arm_status arm_fully_connected_q7_opt(const q7_t * pV,
                                          const q7_t * pM,
                                          const uint16_t dim_vec,
                                          const uint16_t num_of_rows,
                                          const uint16_t bias_shift,
                                          const uint16_t out_shift, 
                                          const q7_t * bias, 
                                          q7_t * pOut, 
                                          q15_t * vec_buffer);

  /**
   * @brief Q15 basic fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>ARM_MATH_SUCCESS</code>
   *
   */

    arm_status arm_fully_connected_q15(const q15_t * pV,
                                       const q15_t * pM,
                                       const uint16_t dim_vec,
                                       const uint16_t num_of_rows,
                                       const uint16_t bias_shift,
                                       const uint16_t out_shift, 
                                       const q15_t * bias, 
                                       q15_t * pOut, 
                                       q15_t * vec_buffer);

  /**
   * @brief Q15 opt fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>ARM_MATH_SUCCESS</code>
   *
   */

    arm_status arm_fully_connected_q15_opt(const q15_t * pV,
                                           const q15_t * pM,
                                           const uint16_t dim_vec,
                                           const uint16_t num_of_rows,
                                           const uint16_t bias_shift,
                                           const uint16_t out_shift,
                                           const q15_t * bias, 
                                           q15_t * pOut, 
                                           q15_t * vec_buffer);

  /**
   * @brief Mixed Q15-Q7 fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>ARM_MATH_SUCCESS</code>
   *
   */

    arm_status arm_fully_connected_mat_q7_vec_q15(const q15_t * pV,
                                                  const q7_t * pM,
                                                  const uint16_t dim_vec,
                                                  const uint16_t num_of_rows,
                                                  const uint16_t bias_shift,
                                                  const uint16_t out_shift,
                                                  const q7_t * bias, 
                                                  q15_t * pOut, 
                                                  q15_t * vec_buffer);

  /**
   * @brief Mixed Q15-Q7 opt fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>ARM_MATH_SUCCESS</code>
   *
   */

    arm_status arm_fully_connected_mat_q7_vec_q15_opt(const q15_t * pV,
                                                      const q7_t * pM,
                                                      const uint16_t dim_vec,
                                                      const uint16_t num_of_rows,
                                                      const uint16_t bias_shift,
                                                      const uint16_t out_shift,
                                                      const q7_t * bias, 
                                                      q15_t * pOut, 
                                                      q15_t * vec_buffer);

/**
 * @brief Matrix-Multiplication Kernels for Convolution
 *
 * These functions are used within convolution layer functions for 
 * matrix multiplication.
 * 
 * The implementation is similar to CMSIS-DSP arm_mat_mult functions
 * with one Q7 and one Q15 operands. The Q15 operand is the im2col
 * output which is always with 2 columns.
 *
 */

  /**
   * @brief Matrix-multiplication function for convolution
   * @param[in]       pA          pointer to operand A
   * @param[in]       pInBuffer   pointer to operand B, always conssists of 2 vectors
   * @param[in]       ch_im_out   numRow of A
   * @param[in]       numCol_A    numCol of A
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        the bias
   * @param[in,out]   pOut        pointer to output
   * @return     The function returns the incremented output pointer
   */

    q7_t     *arm_nn_mat_mult_kernel_q7_q15(const q7_t * pA,
                                            const q15_t * pInBuffer,
                                            const uint16_t ch_im_out,
                                            const uint16_t numCol_A,
                                            const uint16_t bias_shift,
                                            const uint16_t out_shift, 
                                            const q7_t * bias, 
                                            q7_t * pOut);

  /**
   * @brief Matrix-multiplication function for convolution with reordered columns
   * @param[in]       pA          pointer to operand A
   * @param[in]       pInBuffer   pointer to operand B, always conssists of 2 vectors
   * @param[in]       ch_im_out   numRow of A
   * @param[in]       numCol_A    numCol of A
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        the bias
   * @param[in,out]   pOut        pointer to output
   * @return     The function returns the incremented output pointer
   */

    q7_t     *arm_nn_mat_mult_kernel_q7_q15_reordered(const q7_t * pA,
                                                      const q15_t * pInBuffer,
                                                      const uint16_t ch_im_out,
                                                      const uint16_t numCol_A,
                                                      const uint16_t bias_shift,
                                                      const uint16_t out_shift, 
                                                      const q7_t * bias, 
                                                      q7_t * pOut);

#ifdef __cplusplus
}
#endif

/*
 *  Other functions
 *  These layers are typically not timing critical
 *  Basic implementation is supported here
 */

#ifdef __cplusplus
extern    "C"
{
#endif

/**
 * @defgroup Acti Neural Network Activation Functions
 *
 * Perform activation layers, including ReLU (Rectified Linear Unit),
 * sigmoid and tanh
 *
 */

  /**
   * @brief Q7 RELU function
   * @param[in,out]   data        pointer to input
   * @param[in]       size        number of elements
   * @return none.
   */

    void      arm_relu_q7(q7_t * data, uint16_t size);

  /**
   * @brief Q15 RELU function
   * @param[in,out]   data        pointer to input
   * @param[in]       size        number of elements
   * @return none.
   */

    void      arm_relu_q15(q15_t * data, uint16_t size);

  /**
   * @brief Q7 neural network activation function using direct table look-up
   * @param[in,out]   data        pointer to input
   * @param[in]       size        number of elements
   * @param[in]       int_width   bit-width of the integer part, assume to be smaller than 3
   * @param[in]       type        type of activation functions
   * @return none.
   */

    void      arm_nn_activations_direct_q7(q7_t * data, uint16_t size, uint16_t int_width, 
                                           arm_nn_activation_type type);

  /**
   * @brief Q15 neural network activation function using direct table look-up
   * @param[in,out]   data        pointer to input
   * @param[in]       size        number of elements
   * @param[in]       int_width   bit-width of the integer part, assume to be smaller than 3
   * @param[in]       type        type of activation functions
   * @return none.
   */

    void      arm_nn_activations_direct_q15(q15_t * data, uint16_t size, uint16_t int_width,
                                            arm_nn_activation_type type);

/**
 * @defgroup Pooling Neural Network Pooling Functions
 *
 * Perform pooling functions, including max pooling and average pooling
 *
 */

  /**
   * @brief Q7 max pooling function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input
   * @param[in,out]   Im_out      pointer to output tensor
   * @return none.
   *
   */

    void      arm_maxpool_q7_HWC(q7_t * Im_in,
                                 const uint16_t dim_im_in,
                                 const uint16_t ch_im_in,
                                 const uint16_t dim_kernel,
                                 const uint16_t padding,
                                 const uint16_t stride, 
                                 const uint16_t dim_im_out, 
                                 q7_t * bufferA, 
                                 q7_t * Im_out);

  /**
   * @brief Q7 average pooling function
   * @param[in]       Im_in       pointer to input tensor
   * @param[in]       dim_im_in   input tensor dimention
   * @param[in]       ch_im_in    number of input tensor channels
   * @param[in]       dim_kernel  filter kernel size
   * @param[in]       padding     padding sizes
   * @param[in]       stride      convolution stride
   * @param[in]       dim_im_out  output tensor dimension
   * @param[in,out]   bufferA     pointer to buffer space for input
   * @param[in,out]   Im_out      pointer to output tensor
   * @return none.
   *
   */

    void      arm_avepool_q7_HWC(q7_t * Im_in,
                                 const uint16_t dim_im_in,
                                 const uint16_t ch_im_in,
                                 const uint16_t dim_kernel,
                                 const uint16_t padding,
                                 const uint16_t stride, 
                                 const uint16_t dim_im_out, 
                                 q7_t * bufferA, 
                                 q7_t * Im_out);

/**
 * @defgroup Softmax Softmax Functions
 *
 * EXP(2) based softmax function
 *
 */

  /**
   * @brief Q7 softmax function
   * @param[in]       vec_in      pointer to input vector
   * @param[in]       dim_vec     input vector dimention
   * @param[out]      p_out       pointer to output vector
   * @return none.
   *
   */

    void      arm_softmax_q7(const q7_t * vec_in, const uint16_t dim_vec, q7_t * p_out);

  /**
   * @brief Q15 softmax function
   * @param[in]       vec_in      pointer to input vector
   * @param[in]       dim_vec     input vector dimention
   * @param[out]      p_out       pointer to output vector
   * @return none.
   *
   */

    void      arm_softmax_q15(const q15_t * vec_in, const uint16_t dim_vec, q15_t * p_out);

#ifdef __cplusplus
}
#endif

#endif
