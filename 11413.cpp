#include <iostream>
using namespace std;
class Rational
{
    public:
        Rational( int = 0, int = 1 ); // default constructor
        Rational addition( const Rational & ) const; // function addition
        Rational multiplication( const Rational & ) const; // function multi.
        void printRational () const; // print rational format

    private:
        int numerator; // integer numerator
        int denominator; // integer denominator
        void reduce();
}; // end class Rational

int gcd(int a, int b);

void Rational::reduce(){
	int Rationalgcd;
	if(numerator > 0){
		Rationalgcd = gcd(numerator,denominator);
		denominator = denominator/Rationalgcd;
		numerator = numerator/Rationalgcd;
	}
	else{
		Rationalgcd = gcd(-1*numerator,denominator);
		denominator = denominator/Rationalgcd;
		numerator = numerator/Rationalgcd;
	}
	
}

Rational::Rational(int up,int down){
	if(down > 0){
		numerator = up;
		denominator = down;
	}else{
		numerator = -1*up;
		denominator = -1*down;
	}
	
	reduce();
}
Rational Rational::addition(const Rational &y) const{
	Rational ans; 
	ans.denominator = denominator * y.denominator;
	ans.numerator = numerator*y.denominator + y.numerator*denominator;
	ans.reduce();
	return  ans;
}

Rational Rational::multiplication(const Rational &y) const{
	Rational ans;
	ans.numerator = numerator*y.numerator;
	ans.denominator = denominator*y.denominator;
	ans.reduce();
	
	return ans;
}

void Rational::printRational() const{
	cout<<numerator<<"/"<<denominator<<endl;
}

int main()
{
    char s1;
    int s2, s3, s4, s5;

    Rational x;
    while(cin >>s1>>s2>>s3>>s4>>s5)
    {
        if(cin.eof())
        {
		    break;
        }
        Rational c(s2, s3), d(s4, s5);
        if(s1 == '+')
        {
            x = c.addition( d ); // adds object c and d; sets the value to x
            x.printRational(); // prints rational object x
        }
        else if(s1 == '*')
        {
            x = c.multiplication( d ); // multiplies object c and d
            x.printRational(); // prints rational object x
        }
    }
}

int gcd(int a, int b){
    return (b == 0) ? a : gcd(b, a % b);
}
