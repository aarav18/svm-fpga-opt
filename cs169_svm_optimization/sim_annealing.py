from scipy.optimize import dual_annealing
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
import pickle
import time
import numpy as np
import matplotlib.pyplot as plt

with open("X.pk1", "rb") as file:
    X = pickle.load(file)
with open("y.pk1", "rb") as file:
    y = pickle.load(file)

np.random.seed(42)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

data = []

start_time = time.time()

# Define the objective function
def objective(params):
    C, gamma = params
    model = SVC(kernel="rbf", C=C, gamma=gamma, class_weight="balanced")
    # Evaluate the model using cross-validation and return the negative of the mean accuracy
    return -cross_val_score(model, X_train, y_train, cv=5, scoring="accuracy").mean()

# Define the callback function to print the results at each iteration
def callback(x, fval, context):
    current_time = time.time()
    print(f"Current parameters: {x}, Objective value: {fval}, Time Elapsed: {current_time-start_time}")
    print(context)
    data.append(fval)

# Define the bounds for the hyperparameters C, gamma
bounds = [(1e-3, 1e3), (1e-4, 1)]  # Bounds for C, gamma

# Run dual annealing with the callback function
result = dual_annealing(objective, bounds, callback=callback)

# Print the optimized hyperparameters
print("Optimized parameters:", result.x)

# plot validation accuracy over iterations
plt.plot(data)
plt.title("Accuracy vs Iterations of Simulated Annealing")
plt.xlabel("Iterations")
plt.ylabel("Validation Accuracy")
plt.show()