from sklearn.metrics import roc_curve
import pandas as pd
import numpy as np
import sys


def score(idx, submission, test, all_data):
    alpha = 1e-4
    beta = 10
    max_z = abs(all_data).max()
    pred_y = submission.loc[idx.index.values].y.values
    y = idx.y.astype(int)

    pred_z = all_data[idx.index.values.astype(int), pred_y.astype(int)]
    z = all_data[idx.index.values, y]
    y_err = ((pred_y - y)/3000)** 2
    z_err = ((pred_z - z)/max_z) ** 2
    return np.sqrt(np.sum(y_err + z_err))


ans = pd.read_csv(sys.argv[1])

user = pd.read_csv(sys.argv[2])
user['x'] = user['x'].astype(int)
user['y'] = user['y'].astype(int)

idx = pd.read_csv(sys.argv[3])
idx['x'] = idx['x'].astype(int)
idx = idx.set_index('x')
z = np.load('/home/workspace/boosters.pro/backend/metrics/metrics/all_data.npy').astype('float64')

user = user.set_index('x')
ans = ans.set_index('x')

res = score(idx, user, ans, z)

print("ok: {}".format(res))
