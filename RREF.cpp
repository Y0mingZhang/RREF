#include <vector>
#include <iostream>
#include <utility>
#include <cmath>


using namespace std;


const double eps = 1e-8;



typedef vector<vector<double>> matrix;

void interchange(matrix& m, int row1, int row2){
// Swap the positions of two rows.
    swap(m[row1],m[row2]);
}

void scalarMult(vector<double>& row, double mutiple){
// Multiply a row by a non-zero scalar
    for(int i = 0; i < row.size(); ++i){
        row[i] *= mutiple;
    }
}

void add(matrix& m, int row1, int row2, double multiple){
// A method that adds multiple * row2 to row1
    for(int i = 0; i < m[row1].size(); ++i){
        m[row1][i] += m[row2][i] * multiple;
    }
}

// Note: undefined behaviour if matrix has more columns than rows

void RREF(matrix& m){
    // Working down(elimination)
    for(int i = 0; i < m.size(); ++i){
        if(m[i][i] == 0){
            int j = i + 1;
            while(m[j][i] == 0) ++j;
            if(j >= m.size()) continue;
            interchange(m, i, j);
        }
        if(m[i][i] != 1){
            scalarMult(m[i], 1.0 / m[i][i]);
        }
        for(int j = i + 1; j < m.size(); ++j){
            if(m[j][i] != 0){
                scalarMult(m[j], m[i][i]);
                add(m, j, i, -(m[j][i]/m[i][i]));
            }
        }
    }
    
    // Working up(back-substitution)
    for(int i = min(m.size(), m[0].size()) - 1; i >= 0; --i){
        for(int j = i - 1; j >= 0; --j){
            if(m[j][i] != 0){
                add(m, j, i, -(m[j][i]/m[i][i]));
            }
        }
    }
    
}

void print(matrix& m){
    for(auto& r : m){
        for(auto d : r){
            // if statement to deal with negative zero issue in C++
            if(abs(d) < eps) cout << 0;
            else cout << d;
            cout << ' ';
        }
        cout << '\n';
    }
}

int main(){
    // Put your matrix here
    matrix m = {{1,5,1,2},{0,1,0,1.0/3.0}, {0,0,1,1.0/3.0}};
    RREF(m);
    print(m);
}
