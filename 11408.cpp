#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Polynomial
{

public:
    Polynomial();
    Polynomial(const int , const int [51]);
    Polynomial add( const Polynomial) const; // add function
    Polynomial subtract( const Polynomial ) const; // subtract function
    Polynomial multiplication( const Polynomial ) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

Polynomial::Polynomial(){
	greatestPower = 0;
	for(int i=0;i<101;i++)	coefficients[i] = 0;
}
Polynomial::Polynomial(const int n, const int val[51]){
	greatestPower = n;
	for(int i=100;i>greatestPower;i--)	coefficients[i] = 0;
	for(int i=greatestPower;i>=0;i--) 	coefficients[i] = val[i];
}
Polynomial Polynomial::add(const Polynomial b) const{
	Polynomial c;
	int length = (greatestPower > b.greatestPower) ? greatestPower : b.greatestPower;
	c.greatestPower = length;
	
	for(int i=length;i>=0;i--){
		c.coefficients[i] = coefficients[i] + b.coefficients[i]; 
	}
	return c;
}

Polynomial Polynomial::subtract(const Polynomial b) const{
	Polynomial c;
	int length = (greatestPower > b.greatestPower) ? greatestPower : b.greatestPower;
	c.greatestPower = length;
	for(int i=length;i>=0;i--){
		c.coefficients[i] = coefficients[i] - b.coefficients[i]; 
	}
	return c;
}

Polynomial Polynomial::multiplication(const Polynomial b) const{
	Polynomial c;
	int length = greatestPower + b.greatestPower;
	int ans[102];
	
	for(int i=0;i<101;i++) ans[i] = 0;
	
	for(int i=greatestPower;i>=0;i--){
		for(int j=b.greatestPower;j>=0;j--){
			ans[i+j] += coefficients[i] * b.coefficients[j];
		}
	}
	if(length <101){
		c.greatestPower = length;
		for(int i=length;i>=0;i--)	c.coefficients[i] = ans[i];
	}
	else{
		c.greatestPower = 100;
		for(int i=100;i>=0;i--)	 c.coefficients[i] = ans[i];
	}
	return c;
}

void Polynomial::output() const{
	for(int i=greatestPower;i>0;i--){
		cout << coefficients[i] << " ";
	}
	cout << coefficients[0];
	cout << endl;
}

int main()
{
    int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }
    Polynomial a(greatestPower1, coefficient1), b(greatestPower2, coefficient2) ;
	
    ans = a.add( b );
    ans.output();

    ans = a.subtract( b );
    ans.output();

    ans = a.multiplication( b );
    ans.output();

} // end main
