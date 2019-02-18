#include <array>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;


template<class T, long long unsigned int n>
array<array<array<T, n>, n>, n> Add3D(const array<array<array<T, n>, n>, n> A, const array<array<array<T, n>, n>, n> B){
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
    
    auto C = array<array<array<T, n>, n>, n>();

    auto startTime = clock();

//    #pragma omp parallel for
    for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            for(auto k = 0; k < n; k++){
                auto sum = A.at(i).at(j).at(k) + B.at(i).at(j).at(k);
                C.at(i).at(j).at(k) = sum;
            }
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
    const auto n = 20;
    auto A = array<array<array<int, n>, n>, n>();
    auto B = array<array<array<int, n>, n>, n>();
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(0,n-1);
    distribution(generator);
    for (auto i = 0; i < n ; i++){
        for(auto j = 0; j < n ; j++){
            for(auto k = 0; k < n; k++){
                A.at(i).at(j).at(k)=distribution(generator);
                B.at(i).at(j).at(k)=distribution(generator);
            }
        }
    }
    Add3D<int, n>(A, B);
    return 0;
}