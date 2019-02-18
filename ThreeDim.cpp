#include <iostream>
#include <vector>

using namespace std;

int vectorMult(vector<int> A, vector<int> B){
	auto c = 0;
	for(int i = 0; i < A.size(); i++){
			c = c + (A.at(i) * B.at(i));
		
	}
	return c;
}

vector<vector<vector<int>>> rank3TensorMult(vector<vector<vector<int>>> A, vector<vector<vector<int>>> B){
	auto C = A;
	for(int x = 0; x < A.at(0).size(); x++){
		//cout << "x: " << x << endl;
		for(int y = 0; y < A.at(0).size(); y++){
			//cout << "y: " << y << endl;
			for(int k = 0; k < A.at(0).size(); k++){	
				//cout << "k: " << k << endl;

				vector<int> row = vector<int>();
				vector<int> col = vector<int>();	
				for(int i = 0; i < A.at(0).size(); i++){
					//cout << "i: " << i << endl;
					row.push_back(A.at(i).at(y).at(k));//row.at(i) = A.at(i).at(y).at(k);
				}
				for(int j = 0;j < A.at(0).size();j++){
					//cout << "j: " << j << endl;	
					col.push_back(B.at(x).at(j).at(k));//col.at(j) = B.at(x).at(j).at(k);
				}
				C.at(x).at(y).at(k) = vectorMult(row,col);
			}
		}
	}
	return C;
}

int main(){
	auto A = vector<vector<vector<int>>>{ { {1,2} , {3,4} } , { {5,6} , {7,8} } };
	auto B = vector<vector<vector<int>>>{ { {9,10} , {11,12} } , { {13,14} , {15,16} } };
	//cout << "Created" << endl;
	auto C = rank3TensorMult(A,B);
	//cout << "Finished" << endl;
	for(int i = 0; i < C.at(1).size(); i++){
		for(int j = 0; j < C.at(1).size(); j++){
			for(int k = 0; k < C.at(1).size(); k++){
				cout << C.at(i).at(j).at(k) << " ";
			}
			cout << "    " << endl;
		}
		cout << endl;
	}
	return 0;
}
