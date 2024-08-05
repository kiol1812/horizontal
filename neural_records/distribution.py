# show distribution
# 2024/08/05

import numpy as np
import pandas as pd
import matplotlib.pyplot as  plt

data = pd.read_csv("output/dataset.csv")

data = np.array(data)

# print(data.shape)
# print(data[:, 1:2].shape)

x =  data[:, 1:2].reshape(100)
y = np.zeros((1, 100))

plt.scatter(x, y)
plt.show()