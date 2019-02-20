#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

class DimensionsHaveToBeNonZeroPositiveIntegersException{};

template<class T, long long unsigned int n>
array<array<T, n>, n> rank2TensorAdd(const array<array<T, n>, n> A, const array<array<T, n>, n> B){
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
    auto C = array<array<T, n>, n>();
    auto startTime = clock();
    for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            auto sum = A.at(i).at(j) + B.at(i).at(j);
            C.at(i).at(j) = sum;
        }
    }
    auto runTime = clock() - startTime;
    cout << "2D addition ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds." << endl;
    return C;
}

template<class T, long long unsigned int n>
array<array<array<T, n>, n>, n> rank3TensorAdd(const array<array<array<T, n>, n>, n> A, const array<array<array<T, n>, n>, n> B){
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
    auto C = array<array<array<T, n>, n>, n>();
    auto startTime = clock();
    for (auto i = 0; i < n ; i++){
        for (auto j = 0; j < n; j++){
            for(auto k = 0; k < n; k++){
                auto sum = A.at(i).at(j).at(k) + B.at(i).at(j).at(k);
                C.at(i).at(j).at(k) = sum;
            }
        }
    }
    auto runTime = clock() - startTime;
    cout << "3D addition ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds." << endl;
    return C;
}


template<class T, long long unsigned int n>
array<array<T, n>, n> rank2TensorMult(array<array<T, n>, n> A, array<array<T, n>, n> B){ 
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
	auto startTime = clock();
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
    auto runTime = clock() - startTime;
    cout << "2D multiplication ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds." << endl;
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
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
	auto startTime = clock();
    auto C = A;
	for(int x = 0; x < A.at(0).size(); x++){
		for(int y = 0; y < A.at(0).size(); y++){
			for(int k = 0; k < A.at(0).size(); k++){	
				vector<int> row = vector<int>();
				vector<int> col = vector<int>();	
				for(int i = 0; i < A.at(0).size(); i++){
					row.push_back(A.at(i).at(y).at(k));
				}
				for(int j = 0;j < A.at(0).size();j++){
					col.push_back(B.at(x).at(j).at(k));
				}
				C.at(x).at(y).at(k) = vectorMult(row,col);
			}
		}
	}
    auto runTime = clock() - startTime;
    cout << "3D multiplication ran in: " << double(runTime)/(double)CLOCKS_PER_SEC << " seconds." << endl;
	return C;
}

template<class T, long long unsigned int n>
array<array<array<T, n>, n>, n> Generate3DArray(){
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
    auto A = array<array<array<T, n>, n>, n> ();
    default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0,n-1);
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
array<array<T, n>, n> Generate2DArray(){
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
    auto A = array<array<T, n>, n> ();
    default_random_engine generator(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0,n-1);
    distribution(generator);
    for (auto i = 0; i < n ; i++){
        for(auto j = 0; j < n ; j++){
            A.at(i).at(j) = distribution(generator);
        }
    }
    return A;
}

class FileNotOpenException{};

template<class T, long long unsigned int n>
void Save2D(array<array<T, n>, n> Result, ofstream& output){
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
    if(!output.is_open()){
        throw FileNotOpenException{};
    }
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            output<<Result.at(i).at(j)<<" ";

        }
        output<<endl;
    }
    output<<endl<<endl;
}

template<class T, long long unsigned int n>
void Save3D(array<array<array<T, n>, n>, n> Result, ofstream& output){
    if(n <= 0){
        throw DimensionsHaveToBeNonZeroPositiveIntegersException{};
    }
    if(!output.is_open()){
        throw FileNotOpenException{};
    }
    output<<"Front face of cube: "<<endl;
    for(int k = 0; k<n; k++){
        for (int i = 0; i<n; i++){
            for (int j = 0; j<n; j++){
                output<<Result.at(i).at(j).at(k)<<" ";
            }
        output<<endl;
        }
        output<<endl;
    }
    output<<endl<<endl;
}

int main(){
    default_random_engine generator(time(0));
    const long long unsigned int n1 = 10;

    auto Afor2DSmall = Generate2DArray<int, n1>();
    auto Bfor2DSmall = Generate2DArray<int, n1>();
    if(Afor2DSmall.size() != n1 ||  Bfor2DSmall.size() != n1) {
        cout<<"Array not created correctly";
        return 0;
    }
    auto Cfor2DAddSmall = rank2TensorAdd<int, n1>(Afor2DSmall, Bfor2DSmall);
    auto Cfor2DMultSmall = rank2TensorMult<int, n1>(Afor2DSmall,Bfor2DSmall);


    auto Afor3DSmall = Generate3DArray<int, n1>();
    auto Bfor3DSmall = Generate3DArray<int, n1>();
    if(Afor3DSmall.size() != n1 ||  Bfor3DSmall.size() != n1) {
        cout<<"Array not created correctly";
        return 0;
    }
    auto Cfor3DAddSmall = rank3TensorAdd<int, n1>(Afor3DSmall, Bfor3DSmall);
    auto Cfor3DMultSmall = rank3TensorMult<int, n1>(Afor3DSmall, Bfor3DSmall);

    ofstream output;
    output.open("Results.txt");
    
    output<<"First 2D matrix used: "<<endl;
    Save2D<int, n1>(Afor2DSmall, output);

    output<<"Second 2D matrix used: "<<endl;
    Save2D<int, n1>(Bfor2DSmall, output);

    output<<"2D Addition Result: "<<endl;
    Save2D<int, n1>(Cfor2DAddSmall, output);

    output<<"2D Multiplication Result: "<<endl;
    Save2D<int, n1>(Cfor2DMultSmall, output);

    output<<"First 3D matrix used: "<<endl;
    Save3D<int, n1>(Afor3DSmall, output);

    output<<"Second 3D matrix used: "<<endl;
    Save3D<int, n1>(Bfor3DSmall, output);

    output<<"3D Addition Result: "<<endl;
    Save3D<int, n1>(Cfor3DAddSmall, output);

    output<<"3D Multiplication Result: "<<endl;
    Save3D<int, n1>(Cfor3DMultSmall, output);

    const long long unsigned int n2 = 20;

    auto Afor2DLarge = Generate2DArray<int, n2>();
    auto Bfor2DLarge = Generate2DArray<int, n2>();
    if(Afor2DLarge.size() != n2 ||  Bfor2DLarge.size() != n2) {
        cout<<"Array not created correctly";
        return 0;
    }
    auto Cfor2DAddLarge = rank2TensorAdd<int, n2>(Afor2DLarge, Bfor2DLarge);
    auto Cfor2DMultLarge = rank2TensorMult<int, n2>(Afor2DLarge,Bfor2DLarge);

    auto Afor3DLarge = Generate3DArray<int, n2>();
    auto Bfor3DLarge = Generate3DArray<int, n2>();
    if(Afor3DLarge.size() != n2 ||  Bfor3DLarge.size() != n2) {
        cout<<"Array not created correctly";
        return 0;
    }
    auto Cfor3DAddLarge = rank3TensorAdd<int, n2>(Afor3DLarge, Bfor3DLarge);
    auto Cfor3DMultLarge = rank3TensorMult<int, n2>(Afor3DLarge, Bfor3DLarge);

    output<<"First 2D matrix used: "<<endl;
    Save2D<int, n2>(Afor2DLarge, output);

    output<<"Second 2D matrix used: "<<endl;
    Save2D<int, n2>(Bfor2DLarge, output);

    output<<"2D Addition Result: "<<endl;
    Save2D<int, n2>(Cfor2DAddLarge, output);

    output<<"2D Multiplication Result: "<<endl;
    Save2D<int, n2>(Cfor2DMultLarge, output);

    output<<"First 3D matrix used: "<<endl;
    Save3D<int, n2>(Afor3DLarge, output);

    output<<"Second 3D matrix used: "<<endl;
    Save3D<int, n2>(Bfor3DLarge, output);

    output<<"3D Addition Result: "<<endl;
    Save3D<int, n2>(Cfor3DAddLarge, output);

    output<<"3D Multiplication Result: "<<endl;
    Save3D<int, n2>(Cfor3DMultLarge, output);

    output.close();
    return 0;
}
