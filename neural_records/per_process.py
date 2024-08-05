# 寫上資料標籤的程式
# 包含影像紀錄與當下角度值
# 2024/08/05

import cv2
import mpu6050
import time
import math
import numpy as np
import pandas as pd

PI = 3.14159264
mpu6050 = mpu6050.mpu6050(0x68)
def get_angle():
    accelerometer = mpu6050.get_accel_data()
    pitch_angle = math.atan2(accelerometer['y'], accelerometer['z'])*180/PI
    roll_angle = math.atan2(accelerometer['x'], accelerometer['z'])*180/PI
    return pitch_angle, roll_angle

cap = cv2.VideoCapture('/dev/video0', cv2.CAP_V4L)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1440)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1440)

SIZE_OF_DATASET =  100 # temp, 100 is too few
datas = np.zeros((SIZE_OF_DATASET, 16800))
labels = np.zeros((SIZE_OF_DATASET, 1))
index = 0

print("start loop")
while index<SIZE_OF_DATASET:
    p, r = get_angle()
    abs = math.fabs (p)
    if(p>0):
        sign = 1
    else:
        sign = -1
    # print(round((180-abs)*sign, 2))

    ret, frame = cap.read()
    img = cv2.resize(frame, (360, 360), interpolation=cv2.INTER_AREA)

    x, y, h, w = 30, 150, 60, 280 
    crop_img  = img[y:y+h, x:x+w]  # 60 * 280, 16800

    gray = cv2.cvtColor(crop_img, cv2.COLOR_BGR2GRAY)    #gray

    # expend = np.zeros(16800)
    datas[index]  = gray.reshape(16800)
    labels[index] = round((180-abs)*sign, 2)

    index = index+1
    print(index, "%")
    # print(index/10, "%")
    # cv2.imshow("stream", gray)
    cv2.imshow("stream", crop_img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

print("out of loop, release cap.")
cap.release()
cv2.destroyAllWindows()

print("start to save data set, it'll take long time.")
result = np.concatenate((labels, datas), axis=1)
pd.DataFrame(result).to_csv("output/dataset.csv")
print("all complete.")