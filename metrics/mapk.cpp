#include "json/json.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;



double avg_precision_at_k(nlohmann::json y_pred, nlohmann::json y_true, int k) {
    double count = 0;
    double avp = 0;
    int N = k;
    vector<int> v = y_true.get<vector<int>>();
    set<int> s(v.begin(), v.end());
    vector<int> v2 = y_pred.get<vector<int>>();
    if(y_pred.size() < k) N = y_pred.size();
    if(k == 0) return 0;
    for(int i = 0; i < N; i++) {

        count += s.count(v2[i]);
        if(s.count(v2[i]) != 0) {
            s.erase(v2[i]);
            avp += count/(i + 1);
        }
    }
    if(y_true.size() < k) k = y_true.size();
    return avp/k;
}

double mapk(nlohmann::json y_pred, nlohmann::json y_true) {
    double m;
    double N = y_true.size();
    double mm = 0;
    double pr;
    for (auto& i : y_true.items()) {
        if (y_pred.find(i.key()) != y_pred.end()) {
            pr = avg_precision_at_k(y_pred[i.key()], i.value(), 20);
        } else {
            pr = 0;
        }
        m += pr/N;
    }
    return m;
}

int main(int argc, char* argv[]) {

    ifstream in1, in2;
    in1.open(argv[2], ifstream::in);
    in2.open(argv[3], ifstream::in);
    nlohmann::json j1, j2;
    in1 >> j1;

    in2 >> j2;

    cout << "ok:"<< mapk(j1, j2) << endl;

    return 0;
}
