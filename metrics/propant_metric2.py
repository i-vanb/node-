import pandas as pd
import numpy as np
import sys
from metric_utils_mobile import contest_metric
import glob
import subprocess
import os
import numpy as np
import MNN
import time

def convert(model_path):
    base = os.path.dirname(model_path)
    filename = model_path.split('/')[-1][:-5] + '.mnn'

    r = subprocess.run(['python', '-m', 'MNN.tools.mnnconvert',
                        '-f', 'ONNX', '--modelFile', model_path, '--MNNModel',
                        base + f"/{filename}"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    #print(r.returncode)
    return r.returncode == 0, base + f"/{filename}"


def estimate(model):
    times = []
    interpreter = MNN.Interpreter(model)
    session = interpreter.createSession()
    input_tensor = interpreter.getSessionInput(session)
    shape = input_tensor.getShape()
    input_np = np.random.uniform(size=shape).astype(np.float32)
    tmp_input = MNN.Tensor(shape, MNN.Halide_Type_Float,\
                    input_np, MNN.Tensor_DimensionType_Caffe)
    for i in range(100):
        start_time = time.time()
        #session = interpreter.createSession()
        #input_tensor = interpreter.getSessionInput(session)
        #shape = input_tensor.getShape()
        #input_np = np.random.uniform(size=shape).astype(np.float32)
        #tmp_input = MNN.Tensor(shape, MNN.Halide_Type_Float,\
        #            input_np, MNN.Tensor_DimensionType_Caffe)
        input_tensor.copyFrom(tmp_input)
        interpreter.runSession(session)
        output_tensor = interpreter.getSessionOutput(session)
        #output_shape = output_tensor.getShape()
        #tmp_output = MNN.Tensor(output_shape, MNN.Halide_Type_Float, np.ones(output_shape).astype(np.float32), MNN.Tensor_DimensionType_Caffe)
        #output_tensor.copyToHostTensor(tmp_output)
        end_time = time.time()
        times.append(end_time - start_time)
    return np.mean(times)

def estimate_working_time(models):
    times = []
    for model in models:
        times.append(estimate(model))
    return np.sum(times)

# read files
ans = pd.read_csv(sys.argv[1])
sub = pd.read_csv(sys.argv[2])
idx = set(pd.read_csv(sys.argv[3]).ImageId.values)

# deal with not filled images
ans_tu = ans[ans.ImageId.isin(idx)]
sub_tu = sub[sub.ImageId.isin(idx)]

base = os.path.dirname(sys.argv[2])
models = glob.glob(base + '/model_*.onnx')
#print(base)
converted = []
converted_models = []
for model in models:
    status, path = convert(model)
    converted.append(status)
    converted_models.append(path)
if not all(converted) or len(converted) == 0:
    print('Error: converting models to .mnn')
else:
    #print(converted)
    #print(models)
    mean_time = estimate_working_time(converted_models)
    #print('mean_time ', mean_time)
    if len(set(idx).intersection(set(sub_tu.ImageId))) != len(idx):
        print('Error: missing ImageId in submit')
    else:
        res, chi2, mape = contest_metric(ans_tu, sub_tu)
        #print(chi2, mape)
        print("ok: {}".format(res*0.8 + (mean_time/0.5)*0.2))
