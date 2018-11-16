#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

double rand_float() {
    return ( ( double )rand() * 1.5 ) / ( double )RAND_MAX + 0.5;
}

class Matrix {
    
    int size;
    vector<vector<double>> mat;

    public:
    Matrix(int n){
        size = n;
        mat.resize(size, vector<double>(size));
    }

    int get_size(){
        return size;
    }

    double &get_elem(int i, int j){
        return this->mat[i][j];
    }

    static void multiple(Matrix &matrix){
        int size = matrix.size;
        vector<vector<double>> res(size, vector<double>(size));
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                for(int k = 0; k < size; k++)
                    res[i][j] += matrix.get_elem(i, k) * matrix.get_elem(k, j);
        matrix.mat = res;
    }
};

void fill_matrix(Matrix &mat){
    for(int i=0;i<mat.get_size();i++)
        for(int j=0;j<mat.get_size();j++)
            mat.get_elem(i, j) = rand_float();
}

double test(Matrix &m){

    int tests = 1;

    if(m.get_size() == 10) tests = 10;
    if(m.get_size() == 100) tests = 5;

    chrono::duration<double> time_span;
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;

    for(int i=0; i<tests; i++){
        t1 = chrono::high_resolution_clock::now();
        m.multiple(m);
        t2 = chrono::high_resolution_clock::now();
        time_span += chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    }

    return time_span.count();
}

int main() {
    Matrix m10(10);
    Matrix m100(100);
    Matrix m1000(1000);
    Matrix m10000(10000);
    
    fill_matrix(m10);
    fill_matrix(m100);
    fill_matrix(m1000);
    fill_matrix(m10000);

    cout << "A size 10 matrix: "    << test(m10) / 10 << " seconds." << endl;
    cout << "A size 100 matrix: "   << test(m100) / 5 << " seconds." << endl;
    cout << "A size 1000 matrix: "  << test(m1000)    << " seconds." << endl;
    cout << "A size 10000 matrix: " << test(m10000)   << " seconds." << endl;


}