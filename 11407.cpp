#include <iostream>
#include <stdio.h>
#define MATRIX_H
using namespace std;

class Matrix
{

public:
    Matrix();
    Matrix (const int , const int [50][50]);
    Matrix add(const Matrix) const;//add function
    Matrix subtract(const Matrix) const;//subtract function
    Matrix multiplication(const Matrix) const;//multiply function
    Matrix inc() const;//increased by 1
    Matrix Transpose() const;//Transpose function
    void output() const;//Note that each output should be followed by a new
                        //line character.
private:
    int matrix[50][50];
    int matrix_size;
}; //end class Matrix

/*空矩陣*/ 
Matrix::Matrix(){
	int matrix_size = 0;
	for(int i=0; i<50;i++ ){
		for(int j=0;j<50;j++)
			matrix[i][j] = 0;
	}
}

/*以二維陣列值建立矩陣*/ 
Matrix::Matrix(const int n,const int val[50][50]){
	matrix_size = n;
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n;j++)
			matrix[i][j] = val[i][j];
	}
}

//在 C++ 裡 function 後面加const 表示只能取值，所以要建一個空白矩陣改值 
//add function
Matrix Matrix::add(const Matrix b) const{
	Matrix c;
	c.matrix_size = matrix_size;
	for(int i=0 ; i<matrix_size;i++){
		for(int j=0 ; j<matrix_size;j++){
			c.matrix[i][j] = matrix[i][j] + b.matrix[i][j];
		}
	}
	return c;
}
//subtract function 
Matrix Matrix::subtract(const Matrix b) const{
	Matrix c;
	c.matrix_size = matrix_size;
	//cout << c.matrix_size;
	for(int i=0;i<matrix_size;i++){
		for(int j=0;j<matrix_size;j++){
			c.matrix[i][j] = matrix[i][j] - b.matrix[i][j]; 
		}
	}
	return c;
} 
//multiply function
Matrix Matrix::multiplication(const Matrix b) const{
	Matrix c;
	int val;
	c.matrix_size = matrix_size;
	for(int i=0;i<matrix_size;i++){
		for(int j=0;j<matrix_size;j++){
			val = 0;
			for(int k=0; k<matrix_size; k++)	val +=matrix[i][k] * b.matrix[k][j];
			
			c.matrix[i][j] = val;	
		}
	}
	return c;
}
//increased by 1
Matrix Matrix::inc()const{
	Matrix c;
	c.matrix_size = matrix_size;
	for(int i=0;i<matrix_size;i++){
		for(int j=0;j<matrix_size;j++){
			c.matrix[i][j] = (matrix[i][j]+1) % 10;
		}
	}
	return c;
}
//Transpose function
Matrix Matrix::Transpose() const{
	Matrix c;
	c.matrix_size = matrix_size;
	for(int i=0;i<matrix_size;i++){
		for(int j=0;j<matrix_size;j++){
			c.matrix[i][j] = matrix[j][i];		
		}
	}
	return c;
}
void Matrix::output() const{
		
	for(int i=0;i<matrix_size;i++){
		cout << matrix[i][0];
		for(int j=1;j<matrix_size;j++){
			cout << " " << matrix[i][j];
		}
		cout << endl;
	}
}


int main(){
    int N;
    int matrix1[50][50], matrix2[50][50];
    Matrix ans;
    
    cin >> N;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            cin >> matrix1[i][j];
        }
    }
    
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            cin >> matrix2[i][j];
        }
    }
    
    Matrix a(N, matrix1), b(N, matrix2);
    
    ans = a.add( b );
    ans.output();
    cout << endl;
    
    ans = a.subtract( b );
    ans.output();
    cout << endl;
    
    ans = a.multiplication( b );
    ans.output();
    cout << endl;
    
    a.inc().output();
    cout << endl;
	
    b.inc().output();
    cout << endl;
	
    a.Transpose().output();
    cout << endl;
	
    b.Transpose().output();
    
} // end main

