from sklearn.metrics import log_loss
import pandas as pd
import numpy as np
import sys

"""
example of usage:

python mlogloss.py ./input/test_target.csv ./input/sample_submission.csv ./input/pub_id.csv

"""

def mlogloss(true_file="./input/test_target.csv", pred_file="./input/sample_submission.csv", id_file="./input/sample_submission.csv"):
    """
    This function get path to true target and submission file
    return: one value - score
    """
    ids = pd.read_csv(id_file, header=None)
    indicies = ids[ids.iloc[:, 1]==1].index
    y_true = pd.read_csv(true_file, index_col=0, header=None)
    y_pred = pd.read_csv(pred_file, index_col=0)
    return log_loss(np.array(y_true.iloc[indicies]), np.array(y_pred.iloc[indicies]))

def __main__():
    try:
        print 'ok:' + str(mlogloss(sys.argv[1], sys.argv[2], sys.argv[3]))
    except Exception,ex:
        print 'err: ' + str(ex)
__main__()
