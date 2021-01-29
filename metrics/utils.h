#include <iostream>
#include <unordered_map>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct coord {
    double lat, lon;
};

void read_data_csv(string path, unordered_map<int, double> *data);
void read_data_coord(string path, unordered_map<string, coord> *data);
void read_data_coord_2(string path, unordered_map<string, coord> *data1, unordered_map<string, coord> *data2);
int* read_indexes(string path);
string* read_indexes_coords(string path);
void read_mapping(string path, unordered_map<string, double> *data);
void map_data(unordered_map<string, double> mapping, unordered_map<string, double> table, unordered_map<int, double> *transformed);
double roc_auc(unordered_map<int, double> *y_true, unordered_map<int, double> *y_pred, int *ind, int size);
void read_data_csv_n_cols(string path, vector<unordered_map<int, double>> *data, int N);


extern int SIZE;
