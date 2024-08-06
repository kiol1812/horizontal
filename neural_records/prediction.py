import numpy as np
import pandas as pd

W1 = pd.read_csv("train/W1.csv")
W2 = pd.read_csv("train/W2.csv")
b1 = pd.read_csv("train/b1.csv")
b2 = pd.read_csv("train/b2.csv")

def ReLU(Z):
    return np.maximum(Z, 0)

def softmax(Z):
    A = np.exp(Z)/sum(np.exp(Z))
    return A

def forward_prop(W1, b1, W2, b2, X):
    Z1 = W1.dot(X)+b1
    A1 = ReLU(Z1)
    Z2 = W2.dot(A1)+b2
    return softmax(Z2)

def make_prediction(X, W1, b1, W2, b2):
    A2 = forward_prop(W1, b1, W2, b2, X)
    return np.argmax(A2, 0)

target = [] # todo, use camera to produce target
            # refer to train.py
label = 1234 # todo, find label in the same time of produce target
prediction = make_prediction(target, W1, b1, W2, b2)

print("prediction: ", prediction)
print("label: ", label)
