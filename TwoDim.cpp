#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> rank2TensorMult(vector<vector<int>> A, vector<vector<int>> B){
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

int main(){
	auto A = vector<vector<int>>{{1,1},{1,1}};
	auto B = vector<vector<int>>{{2,2},{2,2}};
	auto C = rank2TensorMult(A,B);
	for(int i = 0; i < C.at(1).size(); i++){
		for(int j = 0; j < C.at(1).size(); j++){
			cout << C.at(i).at(j) << " ";
		}
		cout << endl;
	}
	return 0;
}
