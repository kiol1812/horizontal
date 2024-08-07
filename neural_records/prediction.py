# this program get `RuntimeWarning: overflow encountered in exp` warning
# 目前尚未解決。在train.py和bebug.py中沒遇到這個問題，放入的參數大小應該要一樣。
# 可以朝這個方向去嘗試解決
# 2024/08/07

import numpy as np
np.seterr(divide='ignore', invalid='ignore')

import pandas as pd
import cv2
import mpu6050
import math

# format output, refer to train.py
extend = 10
offset = 12*extend

# read params
print("load params")
def load_params():
    W1 = pd.read_csv("train/W1.csv")
    W1 = np.array(W1)
    b1 = pd.read_csv("train/b1.csv")
    b1 = np.array(b1)
    W2 = pd.read_csv("train/W2.csv")
    W2 = np.array(W2)
    b2 = pd.read_csv("train/b2.csv")
    b2 = np.array(b2)
    return W1[:, 1:], b1[:, 1:], W2[:, 1:], b2[:, 1:]
W1, b1, W2, b2 = load_params()

# open camera
print("open camera")
cap = cv2.VideoCapture('/dev/video0', cv2.CAP_V4L)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1440)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1440)

# binding mpu6050 with 0x68
print("init mpu6050")
PI = 3.14159264
mpu6050 = mpu6050.mpu6050(0x68)
def get_angle():
    accelerometer = mpu6050.get_accel_data()
    pitch_angle = math.atan2(accelerometer['y'], accelerometer['z'])*180/PI
    roll_angle = math.atan2(accelerometer['x'], accelerometer['z'])*180/PI
    return pitch_angle, roll_angle

def ReLU(Z): return np.maximum(Z, 0)
def softmax(Z): return np.exp(Z) / sum(np.exp(Z))
def forward_prop(W1, b1, W2, b2, X):
    Z1 = W1.dot(X) + b1
    A1 = ReLU(Z1)
    Z2 = W2.dot(A1) + b2
    return softmax(Z2)
def make_prediction(X, W1, b1, W2, b2):
    A2 = forward_prop(W1, b1, W2, b2, X)
    return np.argmax(A2, 0)

# main begin, could package it into loop
while True: # loop begin
    # get label and target
    p, r = get_angle()
    ret, frame = cap.read()

    # compute target
    img = cv2.resize(frame, (360, 360), interpolation=cv2.INTER_AREA)
    x, y, h, w = 30, 150, 60, 280
    crop = img[y:y+h, x:x+w] # 60*280, 16800
    gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
    target = gray.reshape(16800, 1) # target shape should be (16800, 1)
    
    # compute label
    abs = math.fabs(p)
    if(p>0): sign= 1
    else:    sign=-1
    label = round((180-abs)*sign, 2)

    prediction = make_prediction( target , W1, b1, W2, b2)
    print("prediction: ", (prediction-offset)/extend)
    print("label: ", label)
# end of loop
# end of main