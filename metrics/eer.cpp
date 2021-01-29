    
#include "utils.h"


int SIZE;


double eer(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    
    int *ind;
    unordered_map<int, double> table1, transformed_table;
    unordered_map<string, double> mapping, table2;
    

    read_data_csv(string(argv[1]), &table1);
    read_mapping(string(argv[2]), &table2);
    read_mapping(string(argv[4]), &mapping);
    map_data(mapping, table2, &transformed_table);
    ind = read_indexes(string(argv[3]));

    cout << "ok: " << eer(&table1, &transformed_table, ind, SIZE) << endl;
    
    delete ind, table1, table2;
    return 0;
}

bool sort_f(const pair<int, double> &a, const pair<int, double> &b) {
    return (a.second > b.second);
}

double eer(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {
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
    
    stable_sort(input.begin(), input.end(), sort_f);
    double ones = 0;
    double zeros = 0;
    for(int i = 0; i < size; i++) {
        idx = ind[i];
        if((*y_pred).count(idx)) {
            ones += (*y_true)[idx];
            zeros += (*y_true)[idx] == 0;
        } else {
            cout << "Index does not exist in pred: " << idx << " " << i << endl;
            throw "Wrong index";
        }

    }
    int tps = 0;
    int fps = 0;
    double prevtps, prevfps;
    prevtps = prevfps = -1;

    for(int i = 0; i < size; i++) {
        while ( true) {
            prob = input.at(i).second;
            idx = input.at(i).first;
            tps += (*y_true)[idx];
            fps += 1 - (*y_true)[idx];
            prevfps = fps;
            prevtps = tps;
            if(i == size - 1) break;
            if(abs(prob - input.at(i+1).second) < 1e-16) {
                i++;
            } else {
                break;
            }
        }
        if(double(tps/ones) >= 1 - double(fps/zeros)) {
            cout << i << endl;
            break;
        }
    }
    cout << tps << " " << fps << endl;
    if(tps == prevtps) return (1 - double(tps/ones))*0.5 + (double(fps/zeros))*0.5;
    if(fps == prevfps) return 1 - double(fps/zeros);
    return -1;
}

