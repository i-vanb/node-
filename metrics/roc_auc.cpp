    
#include "utils.h"


int SIZE;


double roc_auc(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    
    int *ind;
    unordered_map<int, double> table1, table2;
    //unordered_map<string, double> mapping, table2;
    

    read_data_csv(string(argv[1]), &table1);
    read_data_csv(string(argv[2]), &table2);
    //read_mapping(string(argv[2]), &table2);
    //read_mapping(string(argv[4]), &mapping);
    //map_data(mapping, table2, &transformed_table);
    ind = read_indexes(string(argv[3]));
    double roc = roc_auc(&table1, &table2, ind, SIZE);
    cout << "ok: " << max(roc, 1 - roc) << endl;
    
    delete ind, table1, table2;
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
