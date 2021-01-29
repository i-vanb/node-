
#include "utils.h"


int SIZE;


double rmsle(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    
    int *ind;
    unordered_map<int, double> table1, table2;
    
    read_data_csv(string(argv[1]), &table1);
    read_data_csv(string(argv[2]), &table2);
    ind = read_indexes(string(argv[3]));
    
    cout << "ok:" << rmsle(&table1, &table2, ind, SIZE) << endl;
    
    delete ind, table1, table2;
    return 0;
}


double rmsle(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {
    double tmp, sum = 0;
    int idx;
    for(int i = 0; i < size; i++) {
        idx = ind[i];
        if((*y_pred).count(idx)) {
            if((*y_pred)[idx] >= 0) {
                
                tmp = log((*y_true)[idx] + 1) - log((*y_pred)[idx] + 1);
                tmp *= tmp;
                sum += tmp / size;
                
            } else {
                cout << "Negative number: " << (*y_pred)[idx] << endl;
            }
            
        } else {
            cout << "Index does not exist: " << idx << endl;
            throw "Wrong index";
        }
    }
    
    return sqrt(sum);
}

