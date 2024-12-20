from pyswarm import pso
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
import pickle
import time
import numpy as np
from matplotlib import pyplot as plt

with open("X.pk1", "rb") as file:
    X = pickle.load(file)
with open("y.pk1", "rb") as file:
    y = pickle.load(file)

np.random.seed(42)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

data = []

start_time = time.time()

def callback(x, fval, context):
    current_time = time.time()
    print(f"Current parameters: {x}, Objective value: {fval}, Time Elapsed: {current_time-start_time}")
    print(context)

def objective(params):
    C, gamma= params
    model = SVC(kernel="rbf", C=C, gamma=gamma, class_weight="balanced")
    model.fit(X_train, y_train)
    val = -cross_val_score(model, X_train, y_train, cv=5, scoring="accuracy").mean()
    data.append(-val)
    return val

# perform PSO
lb = [0.1, 1e-3]  # Lower bounds for C, gamma
ub = [100, 1]      # Upper bounds for C, gamma
xopt, fopt = pso(objective, lb, ub, debug = True)
print(xopt)

# plot validation accuracy over iterations
plt.plot(data)
plt.title("Accuracy vs Iterations of PSO")
plt.xlabel("Iterations")
plt.ylabel("Validation Accuracy")
plt.show()