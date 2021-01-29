#include <iostream>
#include <unordered_map>
#include "utils.h"
#include "math.h"
#define R 0.02
int SIZE;

double hit(unordered_map<string, coord> *y_true, unordered_map<string, coord> *y_pred, string *ind, int size);

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio (false);

    string *ind;
    unordered_map<string, coord> home_true, home_pred, work_true, work_pred;

    read_data_coord_2(string(argv[1]), &home_true, &work_true);
    read_data_coord_2(string(argv[2]), &home_pred, &work_pred);
    ind = read_indexes_coords(string(argv[3]));

    double score_1 = hit(&home_true, &home_pred, ind, SIZE);
    double score_2 = hit(&work_true, &work_pred, ind, SIZE);
    cout << "ok:" << ((score_1 + score_2)/2.0) << endl;

    return 0;
}

double dist_eu(coord a, coord b) {
    double dist;
    dist = sqrt((a.lat - b.lat)*(a.lat - b.lat) + (a.lon - b.lon)*(a.lon - b.lon));
    return dist;
}

double hit(unordered_map<string, coord> *y_true, unordered_map<string, coord> *y_pred, string *ind, int size) {

    double acc = 0;
    double dist = 0;
    string idx;

    for(int i = 0; i < size; i++) {

        idx = ind[i];
        if((*y_pred).count(idx)) {
           dist = dist_eu((*y_true)[idx], (*y_pred)[idx]);
           acc += (dist < R)*1.0/size;
//            cout << acc << " " << dist << endl;
        } else {
                cout << "error:Index does not exist: " << idx << endl;
                throw  "error:Index does not exist";
        }
    }

    return acc;
}
