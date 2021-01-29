
#include "utils.h"


int SIZE;


double wrmsle(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, unordered_map<int, double> *y_w, int *ind, int size);

int main(int argc, char* argv[]) {

    int *ind;
    unordered_map<int, double> table1, table2, table3;
    
    read_data_csv(string(argv[1]), &table1);
    read_data_csv(string(argv[2]), &table2);
    read_data_csv(string(argv[3]), &table3);
    ind = read_indexes(string(argv[4]));
    std::cout.precision(10);
    
    cout << "ok:" << wrmsle(&table1, &table2, &table3, ind, SIZE) << endl;
    
    delete ind, table1, table2;
    return 0;
}

double wrmsle(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, unordered_map<int, double> *y_w, int *ind, int size) {
    double tmp, sum = 0;
    int idx;
    double w = 0;
    for(int i = 0; i < size; i++) {
        idx = ind[i];
        if((*y_pred).count(idx)) {
            if(true) {
                
                tmp =(*y_true)[idx] - (*y_pred)[idx];
                tmp *= tmp;
                sum += tmp * (*y_w)[idx];
                w += (*y_w)[idx];
            } else {
                cout << "Negative number: " << (*y_pred)[idx] << endl;
            }
            
        } else {
            cout << "Index does not exist: " << idx << endl;
            throw "Wrong index";
        }
    }
    
    return sqrt(sum/w);
}

