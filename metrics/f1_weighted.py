from sklearn.metrics import f1_score
import pandas as pd
import numpy as np
import sys



ans = pd.read_csv(sys.argv[1])
ans = ans.set_index(ans.columns[0])

user = pd.read_csv(sys.argv[2])
user = user.set_index(user.columns[0])

idx = pd.read_csv(sys.argv[3])
idx = idx.iloc[:, 0].values


if ans.loc[idx].shape[0] != user.loc[idx].shape[0]:
    print('Error: missing client')
else:
    res = f1_score(ans.loc[idx], user.loc[idx], average='weighted')

    print("ok: {}".format(res))