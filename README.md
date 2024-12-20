---

## **Optimizing SVMs on FPGAs for High-Performance Edge Detection**

---

### **Header 1?**

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
