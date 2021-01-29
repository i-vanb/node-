import pandas as pd
import numpy as np
import sys
from metric_utils import contest_metric

# read files
ans = pd.read_csv(sys.argv[1])
sub = pd.read_csv(sys.argv[2])
idx = set(pd.read_csv(sys.argv[3]).ImageId.values)

# deal with not filled images
ans_tu = ans[ans.ImageId.isin(idx)]
sub_tu = sub[sub.ImageId.isin(idx)]

if len(set(idx).intersection(set(sub_tu.ImageId))) != len(idx):
    print('Error: missing ImageId in submit')
else:
    res, chi2, mape = contest_metric(ans_tu, sub_tu)
    #print(chi2, mape)
    print("ok: {}".format(res))
