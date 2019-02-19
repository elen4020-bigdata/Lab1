#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

template<class T, long long unsigned int n>
array<array<T, n>, n> rank2TensorAdd(const array<array<T, n>, n> A, const array<array<T, n>, n> B){
   
    auto C = array<array<T, n>, n>();

    auto startTime = clock();

//    #pragma omp parallel for
    for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            auto sum = A.at(i).at(j) + B.at(i).at(j);
            C.at(i).at(j) = sum;
        }
    }

    auto runTime = clock() - startTime;
    cout << "Ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds" << endl;
    return C;
}

template<class T, long long unsigned int n>
array<array<array<T, n>, n>, n> rank3TensorAdd(const array<array<array<T, n>, n>, n> A, const array<array<array<T, n>, n>, n> B){
   
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

    auto runTime = clock() - startTime;
    cout << "Ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds" << endl;
    return C;
}


template<class T, long long unsigned int n>
array<array<T, n>, n> rank2TensorMult(array<array<T, n>, n> A, array<array<T, n>, n> B){ 
	auto C = A;
	for(int i = 0; i < A.at(1).size(); i++){
		for(int j = 0; j < A.at(1).size(); j++){
			int c = 0;			
			for(int k = 0; k < A.size();k++){
				c = c + (A.at(i).at(k) * B.at(j).at(k));
			}
			C.at(i).at(j) = c;
		}
		
	}
	return C;
}

int vectorMult(vector<int> A, vector<int> B){
	auto c = 0;
	for(int i = 0; i < A.size(); i++){
			c = c + (A.at(i) * B.at(i));
		
	}
	return c;
}

template<class T, long long unsigned int n>
array<array<array<T, n>, n>, n> rank3TensorMult(array<array<array<T, n>, n>, n> A, array<array<array<T, n>, n>, n> B){
	auto C = A;
	for(int x = 0; x < A.at(0).size(); x++){
		for(int y = 0; y < A.at(0).size(); y++){
			for(int k = 0; k < A.at(0).size(); k++){	
				vector<int> row = vector<int>();
				vector<int> col = vector<int>();	
				for(int i = 0; i < A.at(0).size(); i++){
					row.push_back(A.at(i).at(y).at(k));//row.at(i) = A.at(i).at(y).at(k);
				}
				for(int j = 0;j < A.at(0).size();j++){
					col.push_back(B.at(x).at(j).at(k));//col.at(j) = B.at(x).at(j).at(k);
				}
				C.at(x).at(y).at(k) = vectorMult(row,col);
			}
		}
	}
	return C;
}

template<class T, long long unsigned int n>
array<array<array<T, n>, n>, n> Generate3DArray(){
    auto A = array<array<array<T, n>, n>, n> ();
    default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());//default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(0,n);
    distribution(generator);
    for (auto i = 0; i < n ; i++){
        for(auto j = 0; j < n ; j++){
            for (auto k = 0; k < n; k++){
                 A.at(i).at(j).at(k) = distribution(generator);
            }
        }
    }
    return A;
}

template<class T, long long unsigned int n>
array<array<T, n>, n> Generate2DVector(){
    auto A = array<array<T, n>, n> ();
    default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());//default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(0,n-1);
    distribution(generator);
    for (auto i = 0; i < n ; i++){
        for(auto j = 0; j < n ; j++){
            A.at(i).at(j) = distribution(generator);
            cout << A.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    return A;
}

int main(){
    default_random_engine generator(time(0));
    const int n = 10;

    auto A = Generate2DVector<int, n>();//auto A = Generate2DVector();
    auto B = Generate2DVector<int, n>();//auto B = Generate2DVector();
    
/*    uniform_int_distribution<int> distribution(0,n-1);
    distribution(generator);
    for (auto i = 0; i < n ; i++){
        for(auto j = 0; j < n ; j++){
            A.at(i).at(j)=distribution(generator);
            B.at(i).at(j)=distribution(generator);
        }
    }
    */
    rank2TensorAdd<int, n>(A, B);
    return 0;
}
