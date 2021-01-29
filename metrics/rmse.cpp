
#include "utils.h"


int SIZE;


double rmse(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    
    int *ind;
    unordered_map<int, double> table1, table2;
    
    read_data_csv(string(argv[1]), &table1);
    read_data_csv(string(argv[2]), &table2);
    ind = read_indexes(string(argv[3]));
    
    cout << "ok:" << rmse(&table1, &table2, ind, SIZE) << endl;
    
    delete ind, table1, table2;
    return 0;
}


double rmse(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {
    double tmp, sum = 0;
    int idx;
    for(int i = 0; i < size; i++) {
        idx = ind[i];
        if((*y_pred).count(idx)) {
            
                
           tmp = (*y_true)[idx] - (*y_pred)[idx];
           tmp *= tmp;
           sum += tmp / size;
                
            
           //cout << "Negative number: " << (*y_pred)[idx] << endl;
            
            
        } else {
            cout << "Index does not exist: " << idx << endl;
            throw "Wrong index";
        }
    }
    
    return sqrt(sum);
}

