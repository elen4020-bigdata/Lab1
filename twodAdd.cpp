#include <array>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;


template<class T, long long unsigned int n>
array<array<T, n>, n> Add2D(const array<array<T, n>, n> A, const array<array<T, n>, n> B){
    /*for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            cout << A.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;
    for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            cout << B.at(i).at(j);
        }
        cout << endl;
    }*/
    
    auto C = array<array<T, n>, n>();

    auto startTime = clock();

//    #pragma omp parallel for
    for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            auto sum = A.at(i).at(j) + B.at(i).at(j);
            C.at(i).at(j) = sum;
        }
    }
    
    /*for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            cout << C.at(i).at(j);
        }
        cout << endl;
    }*/
    auto runTime = clock() - startTime;
    cout << "Ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds" << endl;
    return C;
}

int main(){
    const auto n = 600;
    auto A = array<array<int, n>, n>();
    auto B = array<array<int, n>, n>();
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(0,n-1);
    distribution(generator);
    for (auto i = 0; i < n ; i++){
        for(auto j = 0; j < n ; j++){
            A.at(i).at(j)=distribution(generator);
            B.at(i).at(j)=distribution(generator);
        }
    }
    Add2D<int, n>(A, B);
    return 0;
}