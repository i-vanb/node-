import numpy as np
import pandas as pd

sieves_names = [6,7,8,10,12,14,16,18,20,25,30,35,40,45,50,60,70,80,100,'pan']
sieves_names = [str(i) for i in sieves_names]

fraction_sievs = {
        '10/14' : {'all': ['7', '10', '12', '14', '16', '18', '20'], 'main': ['12', '14'], 'rough':'7' },
        '10/16' : {'all': ['6', '10', '12', '14', '16', '20'], 'main': ['12', '14', '16'], 'rough':'6' },
        '12/18' : {'all' : ['8', '12', '14', '16', '18', '20', '30'], 'main': ['14', '16', '18'], 'rough':'8' },
        '12/20' : {'all' : ['8', '12', '14', '16', '18', '20', '30'], 'main': ['14', '16', '18', '20'], 'rough':'8' },
        '16/20' : {'all' : ['12', '16', '18', '20', '25', '30', '40'], 'main': ['18', '20'], 'rough':'12' },
        '16/30' : {'all' : ['12', '16', '18', '20', '25', '30', '40'], 'main': ['18', '20', '25', '30'], 'rough':'12' },
        '20/40' : {'all' : ['16', '20', '25', '30', '35', '40', '50'], 'main': ['25', '30', '35', '40'], 'rough':'16' },
        '30/50' : {'all' : ['20', '30', '40', '45', '50', '60', '70'], 'main': ['40', '45', '50'], 'rough':'20' },
        '40/70' : {'all' : ['30', '40', '45', '50', '60', '70', '100'], 'main': ['45', '50', '60', '70'], 'rough':'30' },
        '20/40_pdcpd_bash_lab' : {'all' : ['12', '16', '18', '20', '25', '30', '40'], 'main': ['25', '30', '40'], 'rough':'12' }
}

true_cols = ['6_true','7_true', '8_true',
           '10_true', '12_true', '14_true', '16_true', '18_true', '20_true',
           '25_true', '30_true', '35_true', '40_true', '45_true', '50_true',
           '60_true', '70_true', '80_true', '100_true', 'pan_true']
pred_cols = ['6_pred', '7_pred', '8_pred', '10_pred', '12_pred', '14_pred', '16_pred',
           '18_pred', '20_pred', '25_pred', '30_pred', '35_pred', '40_pred',
           '45_pred', '50_pred', '60_pred', '70_pred', '80_pred', '100_pred','pan_pred']
cols =  ['6', '7', '8', '10', '12', '14', '16', '18', '20', '25', '30',
       '35', '40', '45', '50', '60', '70', '80', '100', 'pan']


def contest_metric(true_labels, submission):
    """
    Полный пайплайн расчета метрики.
    Аргументы:
    true_labels - pd.DataFrame с true разметкой 
    submission - pd.DataFrame содержащий размеры гранул

    Вернёт:
    Значение итоговой метрики (одно число)
    """
    sub_prep = prepare_sieves_hist_df(submission, true_labels)
    prop_count_df = prepare_prop_count_df(submission, true_labels)
    return metric(sub_prep, prop_count_df)



def metric(bin_hist_sub_df, prop_count_sub_df, a=0.6, b=0.4):
    """
    Расчёт итоговой метрики.
    Аргументы:
    bin_hist_sub_df - pd.DataFrame содержащий true и pred колонки по каждому бину (ситам)
    prop_count_sub_df - pd.DataFrame содержащий true и pred колонки по количеству гранул
    a - коэффициент для ошибки совпадения гистограмм (chi2)
    b - коэффициент для ошибки определения количества гранул (mape)
    Вернёт:
    Значение итоговой метрики (одно число)
    """
    bin_hist_sub_df['chi2'] = bin_hist_sub_df.apply(lambda x: calc_chi_square_metric(x[true_cols].values,
                                                                    x[pred_cols].values,
                                                                    x['fraction']), axis=1)
    chi2 = bin_hist_sub_df['chi2'].mean()

    prop_count_sub_df['mape'] = np.abs(prop_count_sub_df['prop_count_true'] - prop_count_sub_df['prop_count_pred']) / prop_count_sub_df['prop_count_true']
    mape = prop_count_sub_df['mape'].mean()
    return a*chi2 + b*mape, chi2, mape



def prepare_prop_count_df(submission_df, test_labels_df):
    """
    Подготовит датафрейм для подсчёта ошибки определения количества гранул.
    Аргументы:
    submission_df - pd.DataFrame в формате ImageId | prop_size
    test_labels_df - pd.DataFrame содержащий истинные метки для распределений по ситам и количеству гранул
    Вернёт:
    pd.DataFrame содержащий true и pred колонки по количеству гранул
    """

    prop_count_pred = submission_df[['ImageId','prop_count']]
    prop_count_pred.columns = ['ImageId','prop_count_pred']
    prop_count_true = test_labels_df[~test_labels_df['prop_count'].isna()][['ImageId', 'prop_count']].copy()
    prop_count_true.columns = ['ImageId', 'prop_count_true']
    prop_count_df = pd.merge(prop_count_pred, prop_count_true, on='ImageId')
    return prop_count_df

def prepare_sieves_hist_df(submission_df, test_labels_df_in, result_bins=None):
    """
    Подготовит датафрейм для подсчёта ошибки совпадения гистограмм.
    Аргументы:
    submission_df - pd.DataFrame в формате ImageId | prop_size
    test_labels_df - pd.DataFrame содержащий истинные метки для распределений по ситам и количеству гранул
    Вернёт:
    pd.DataFrame содержащий true и pred колонки по каждому бину (ситам)
    """
    test_labels_df = test_labels_df_in.copy()
    if result_bins is None:
        result_bins = submission_df.copy()
        result_bins.rename(lambda x: str(x) + '_pred' if x!='ImageId' else x, axis='columns',inplace=True)
        result_bins.reset_index(inplace=True)
    test_labels_df.rename(lambda x: str(x) + '_true' if x in cols else x, axis='columns', inplace=True)

    sieves_hist_df = pd.merge(result_bins,test_labels_df, on='ImageId')
    sieves_hist_df = sieves_hist_df[~sieves_hist_df['pan_true'].isna()].drop('prop_count', axis=1).copy()
    return sieves_hist_df


def postprocess_dists(true, pred, sieve_mask):
    true = np.append(true, 0.0)
    pred = np.append(pred, 0.0)

    non_zero_bins = np.argwhere(sieve_mask)
    non_zero_bins = np.insert(non_zero_bins, 0 ,-1, axis=0)
    
    for i, j in zip(non_zero_bins[:-1], non_zero_bins[1:]):
        pred[j] = np.sum(pred[i[0]+1:j[0]+1])

    pred[-1] = np.sum(pred[non_zero_bins[-1][0]+1: ])

    pred[np.argwhere(sieve_mask==0)[:-1]] = 0.0
    true[-1] = np.maximum(0.0, 1.0 - np.sum(true[:-1]))
    return true, pred

def calc_chi_square_metric(true_hist, pred_hist, fraction):
    sieve_mask = np.array([1 if x in fraction_sievs[fraction]['all'] else 0 for x in sieves_names])
    true_hist_processed, pred_hist_processed = postprocess_dists(true_hist, pred_hist, sieve_mask)
    return chi_square_metric(true_hist_processed, pred_hist_processed)

def chi_square_metric(true, pred):
    """
    Возвращает значение метрики хи-квадрат на прогнозе и реальном значении
    """
    mask = ((true==0.0) & (pred==0.0)) | pd.isna(true) | pd.isna(pred)
    true = true[mask==False]
    pred = pred[mask==False]
    distances = ((true-pred)**2)/(true+pred)
    distances[(true==0.0) & (pred==0.0) | (pd.isna(distances))] = 0.0
    return np.sum(distances)/2


