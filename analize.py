from matplotlib import pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from scipy.stats import chisquare
import inspect

X = list()
Y = list()

loff = 0.01
delta = 0.1
points = 1000

file_name = f"optm loff={loff} delta={delta} points={points}"

with open(file_name, "r") as file:
    for line in file:
        x_i, y_i = line.split(",")
        X.append(float(x_i))
        Y.append(float(y_i))

def fit(x, a, b, c):
    return a / (x ** b) + c

popt, pcov = curve_fit(fit, X, Y, maxfev=5000)
x_fit = np.linspace(min(X), max(X))
y_fit = fit(x_fit, *popt)

print(fit(1, *popt))

sigma = np.sqrt(np.diag(pcov))

error = np.sum((np.square(np.array(Y) - fit(np.array(X), *popt))) / np.array(Y))
print(f"chi: {error}")

out = chisquare(fit(np.array(X), *popt), f_exp=np.array(Y), axis=None)
print(out)

sig = inspect.signature(fit)
param_names = list(sig.parameters.keys())
for i in range(len(popt)):
    print(f"{param_names[i+1]}: {popt[i]} +- {sigma[i]}")

plt.plot(X, Y, "ko")
plt.plot(x_fit, y_fit)
plt.show()

