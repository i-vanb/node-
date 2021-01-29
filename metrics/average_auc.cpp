    
#include "utils.h"
#pragma warning( disable : 4101)

int SIZE;


double roc_auc(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    
    int *ind;
    vector<unordered_map<int, double>> table1;
    vector<unordered_map<int, double>> table2;
    //unordered_map<string, double> mapping, table2;
    

    read_data_csv_n_cols(string(argv[1]), &table1, 6);
    read_data_csv_n_cols(string(argv[2]), &table2, 6);

    //read_mapping(string(argv[2]), &table2);
    //read_mapping(string(argv[4]), &mapping);
    //map_data(mapping, table2, &transformed_table);
    ind = read_indexes(string(argv[3]));

    double ans1 = roc_auc(&table1[0], &table2[0], ind, SIZE);
    double ans2 = roc_auc(&table1[1], &table2[1], ind, SIZE);
    double ans3 = roc_auc(&table1[2], &table2[2], ind, SIZE);
    double ans4 = roc_auc(&table1[3], &table2[3], ind, SIZE);
    double ans5 = roc_auc(&table1[4], &table2[4], ind, SIZE);
    //cout << table2[0][2004] << endl;
    cout << "auc: " << ans1 << " " << ans2 << " " << ans3 << " " << ans4 << " " << ans5 << endl;
    cout << "ok: " << 0.2*(ans1 + ans2 + ans3 + ans4 + ans5) << endl;

    return 0;
}


bool sort_f(const pair<int, double> &a, const pair<int, double> &b) {
    return (a.second < b.second);
}

double roc_auc(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {
    double tmp, sum = 0;
    double thr, tp, tn, acc, tp0;
    double prob;
    int idx;
    vector<pair<int, double>> input;
    for(int i = 0; i < size; i++) {
        idx = ind[i];
        if((*y_pred).count(idx)) {
            input.push_back(pair<int, double>(idx, (*y_pred)[idx]));
        } else {
            cout << "Index does not exist: " << idx << " "<< i << endl;
            throw "Wrong index";
        }
    }
    
    sort(input.begin(), input.end(), sort_f);
    double ones = 0;
    for(int i = 0; i < size; i++) {
        idx = ind[i];
        if((*y_pred).count(idx)) {
            ones += (*y_true)[idx];
        } else {
            cout << "Index does not exist in pred: " << idx << " " << i << endl;
            throw "Wrong index";
        }

    }
    thr = 0;
    tp = tp0 = ones;
    acc = tn = 0;
    thr = input.at(0).second;
    for(int i = 0; i < size; i++) {
        prob = input.at(i).second;
//         cout << prob << endl;
        idx = input.at(i).first;
        if(input.at(i).second != thr) {
            thr = prob;
            acc += tn*(tp + tp0);
            tp0 = tp;
            tn = 0;
        }
        tn += 1 - (*y_true)[idx];
        tp -= (*y_true)[idx];
    }
    acc += tn*(tp + tp0);
    return acc/(2*ones*(size - ones));
}
