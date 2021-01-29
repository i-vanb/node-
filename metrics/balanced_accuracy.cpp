#include "utils.h"

int SIZE;


double balanced_accuracy(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio (false);

    int *ind;
    unordered_map<int, double> table1, transformed_table;
    unordered_map<string, double> mapping, table2;

    read_data_csv(string(argv[1]), &table1);
    read_mapping(string(argv[2]), &table2);
    read_mapping(string(argv[4]), &mapping);
    map_data(mapping, table2, &transformed_table);
    ind = read_indexes(string(argv[3]));


    double ba = balanced_accuracy(&table1, &transformed_table, ind, SIZE);

    cout << "ok:" << ba << endl;

    delete ind, table1, table2;
    return 0;
}


double balanced_accuracy(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {

    double tp, tn, p, n;
    int idx;

    tp = tn = p = n = 0;

    for(int i = 0; i < size; i++) {

        idx = ind[i];
        if((*y_pred).count(idx)) {
            if((*y_pred)[idx] == 1 || (*y_pred)[idx] == 0) {
                if((*y_true)[idx] == 1) {
                    p++;
                    if((*y_pred)[idx] == 1) tp++;
                } else {
                    n++;
                    if((*y_pred)[idx] == 0) tn++;
                }
            } else {
                cout << "error:Wrong prediction: " << (*y_pred)[idx] << endl;
                throw "error:Wrong prediction";
            }
        } else {
                cout << "error:Index does not exist: " << idx << endl;
                throw  "error:Index does not exist";
        }
    }


    return (tp/p + tn/n)/2.0;
}
