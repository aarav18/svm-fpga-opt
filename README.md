---

## **Optimizing SVMs on FPGAs for High-Performance Edge Detection**

---

### **Header 1?**

### **5. Results**

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
