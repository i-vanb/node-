#include "utils.h"

int SIZE;


double accuracy(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio (false);

    int *ind;
    unordered_map<int, double> table1, table2;

    read_data_csv(string(argv[1]), &table1);
    read_data_csv(string(argv[2]), &table2);
    ind = read_indexes(string(argv[3]));

    double accuracy_score = accuracy(&table1, &table2, ind, SIZE);

    cout << "ok:" << accuracy_score << endl;

    delete ind, table1, table2;
    return 0;
}

double accuracy(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size) {

    double acc = 0;
    int idx;

    for(int i = 0; i < size; i++) {

        idx = ind[i];
        if((*y_pred).count(idx)) {
           acc += ((*y_true)[idx] == (*y_pred)[idx])*1.0/size;
        } else {
                cout << "error:Index does not exist: " << idx << endl;
                throw  "error:Index does not exist";
        }
    }

    return acc;
}
