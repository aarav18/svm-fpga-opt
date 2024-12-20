---

## **Optimizing SVMs on FPGAs for High-Performance Edge Detection**

---

### **Project Statement**

This project explores the development and optimization of a hardware-based Support Vector Machine (SVM) classifier for real-time image processing. SVMs are powerful machine learning models commonly used for classification tasks. The primary goal is to implement an SVM classifier using an FPGA for high-throughput and low-latency applications. By leveraging the FPGA's spatial parallelism, the project seeks to achieve efficient real-time processing and evaluate its performance against traditional methods.

The objectives are:  
- Train a an SVM and fine tune it using multiple optimization strategies, namely Simulated Annealing and Particle Swarm Optimization (PSO).
- To design and implement an SVM classifier optimized for FPGA using high-level synthesis (HLS).  
- To explore key optimization strategies such as pipelining and parallelism for efficient hardware utilization.
- To validate the implementation on the Zynq ZedBoard FPGA and compare it to software-based implementations in terms of throughput, latency, and resource utilization.  

### **Implementation**

#### 4.1 SVM Algorithm Design  
The SVM model is designed to process high-resolution images (e.g., 1360 x 800) at 60 frames per second. Feature values are normalized using the formula:  
$x' = -1 + 2 \cdot \frac{x - \text{min}}{\text{max} - \text{min}}$

#####4.1.1
The SVM is trained using the BSDS500 dataset. Images are first converted to grayscale, and then the gradient magnitude is computed via the Sobel filter. An even sampling of edge and non-edge pixels is taken from each image, ensuring balanced representation. The training data is scaled using a StandardScaler to normalize the values for optimal model training.
#####4.1.2
- The SVM is trained with an RBF (Radial Basis Function) kernel, which transforms data into a higher-dimensional space, allowing for effective classification of non-linearly separable data. The RBF kernel calculates the similarity between data points based on their Euclidean distance, enhancing the model's ability to capture complex patterns.
- The SVM is trained on a small sample of the dataset, and then optimized first using Simmulated Annealing, and then with Particle Swarm Optimization. Hyperparameters C and gamma are fine-tuned.
- Once final hyperparameters are determined, the final model is trained on the final full dataset and is then ready for FPGA implementation

#### 4.2 FPGA Implementation

#### 4.2.1 FPGA HLS Implementation
- **Development Tool:** Xilinx Vivado, Xilinx Vitis.  
- **Translation Process:** Adapt the optimized C++ Sobel and Box Blur algorithms for FPGA using HLS pragmas.  
- **Optimizations:**  
  - Loop unrolling for parallelizing kernel computations.  
  - Dataflow pipelining for enhanced throughput.  
- **Hardware Validation**
  - The SVM classifier was implemented on the Zynq 7000 ZedBoard FPGA. The system processed 1360 x 800 resolution images at 100 MHz, achieving 60 fps real-time performance.

##### 4.2.2 Modular Design of the SVM Classifier  
The FPGA implementation consists of the following modules:
- **Vector Calculation Module:** Computes $\|x-v\|^2$ for support vectors.  
- **Exponent Calculation Module:** Applies the RBF kernel formula $-\gamma \cdot \|x-v\|^2$.  
- **Taylor Series Approximation Module:** Computes $e^{-\gamma \cdot \|x-v\|^2}$ using a fixed-point approximation.  
- **Coefficient Calculation Module:** Multiplies the kernel output by learned coefficients.  
- **D(x) Calculation Module:** Aggregates results to determine classification output.  

##### 4.2.3 Optimizations  
- Enables parallel computation for feature extraction and classification.  
- Increases throughput by overlapping computation stages.  

### **Results**

#### Performance Analysis and Comparison
| Process | Software (ms) | Software & Hardware (ms) |
| ------- | ------------- | ------------------------ |
| Data Input | 524.44 | 524.44 |
| Segmentation | 6,141.55 | 6,141.55 |
| HOG | 896.14 | 896.14 |
| Mapping | 75.16 | 75.16 |
| **Classification** | 712,000 | 75.34 |
| Output | 41.21 | 41.21 |
| **Total** | 719,678.5 | 7,753.84 |

**Table 1**: **Execution Time Analysis**  
The above table compares the execution time of the classification algorithm when performed solely in software versus when utilizing the proposed hardware accelerator. When using software alone, the classification process required **712,000 ms (712 seconds)**. In contrast, the hardware accelerator reduced the execution time to **75.34 ms**.

It is important to note that this measurement includes the time taken for the software to prepare the data for the next frame while the hardware processes the current frame. This preparation time does not impact the actual system's overall performance.<br></br>

#### Optimization Methods Analysis and Comparison
| Method | Accuracy | Optimal C | Optimal γ |
| ------ | -------- | --------- | --------- |
| Simulated Annealing | 0.791 | 1.01327578 | 0.00081 |
| Particle Swarm | 0.791 | 0.80591537 | 0.001 |

**Table 2**: **Optimization Method Analysis**  
The above table compares the performance of two optimization algorithms for hyperparameter optimization: Simulated Annealing and Particle Swarm Optimization (PSO). For SVMs, the classical hyperparameters are C, the regularization parameter, and gamma (γ), the kernel coefficient.

Both algorithms yielded similar results in terms of validation accuracy and optimal hyperparameters, as shown in the graphs below.

![](https://drive.google.com/uc?export=view&id=1Cjlo3SGME3P5yjPDprHke-jzr2NHt0e7)
![](https://drive.google.com/uc?export=view&id=1ARqAK6BGt5a8UXNFg7D1u9MmPtk3HrDC)

### **Conclusion**

This project successfully demonstrates the design, implementation, and optimization of a hardware-accelerated SVM classifier for real-time image processing using FPGA technology. By leveraging the inherent parallelism and pipelining capabilities of FPGAs, the classifier achieved significant performance improvements over traditional software-based implementations. Key outcomes include:  
1. **Performance Gains**: The proposed FPGA-based classifier reduced the execution time of the classification task from 712 seconds (software-only) to 75.34 milliseconds, representing a dramatic enhancement in processing speed. This improvement highlights the effectiveness of using FPGAs for computationally intensive machine learning tasks.  

2. **Optimized FPGA Implementation**: The modular architecture, featuring components such as Vector Calculation, Exponent Calculation, and Taylor Series Approximation, was meticulously optimized using techniques like loop unrolling and dataflow pipelining. These optimizations enabled parallel computations and minimized latency, ensuring high throughput and real-time processing at 60 frames per second.  

3. **Real-World Viability**: The classifier was validated on the Zynq ZedBoard FPGA, demonstrating its capability to process high-resolution images (1360 x 800) efficiently. The integration of software and hardware processing workflows ensured seamless data preparation and classification, making the system practical for real-world applications.
