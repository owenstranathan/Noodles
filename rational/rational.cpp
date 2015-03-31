/*
RATIONAL.CPP DEFINITIONS FOR CLASS MEMBER FUNCTIONS AND OUT OF CLASS FUNCTIONS
FOR USE WITH RATIONAL TYPES(DECLARED IN RATIONAL.HPP)

AUTHOR: OWEN D STRANATHAN


*/

#include <iostream>
#include <cmath>
#include <string>

#include "rational.hpp"


Rational::Rational() : n(0), d(1){
  //private
}


Rational::Rational(int numerator, int denominator) : n(numerator){
  //if setting the denominator fails then then an error is thrown
  if(denominator == 0){
    throw "Error in initialization of Rational with 0 denominator";
  }
  else{
    d = denominator;
    reduce();
  }
}

void Rational::setNumerator(int numerator){
  n = numerator;
}

void Rational::setDenominator(int denominator){
  if(denominator == 0){
    throw "Error in initialization of Rational with 0 denominator";
  }
  else{
    d = denominator;
    return;
  }
}

void Rational::set(int numerator, int denominator){
  n = numerator;
  if(denominator == 0){
    throw "Error in initialization of Rational with 0 denominator";
  }
  else{
    d= denominator;
    reduce();
  }
}

//gets members for you to paruse
int Rational::getNumerator() const{
  return n;
}

int Rational::getDenominator() const{
  return d;
}

void Rational::reduce(){
  int GCD = gcd(n,d);
  n = n / GCD;
  d = d / GCD;
  if( d < 0){
    d = d*-1;
    n = n*-1;
  }
  return;
}


void Rational::operator=(const Rational& r){
  this->n = r.n;
  this->d = r.d;
  this->reduce();
  return;
}

//////////////////////////////////////////////////////
//ARITHMETIC AND BOOLEAN OPERATORS FOR TWO RATIONALS//
//////////////////////////////////////////////////////

Rational operator+(const Rational& r1, const Rational& r2){
  //Common denominator of the two rationals
  int comDenom = r1.getDenominator() * r2.getDenominator();
  //adjusted numerators of the two rationals added together
  int num = (r1.getNumerator() *r2.getDenominator()) + (r2.getNumerator() * r1.getDenominator());
  //Rational containing the new value
  Rational r3(num, comDenom);
  r3.reduce();
  return r3;
}

Rational operator-(const Rational& r1, const Rational& r2){
  //Common denominator of the two rationals
  int comDenom = r1.getDenominator() * r2.getDenominator();
  //adjusted numerators of the two rationals added together
  int num = (r1.getNumerator() *r2.getDenominator()) - (r2.getNumerator() * r1.getDenominator());
  //Rational containing the new value
  Rational r3(num, comDenom);
  r3.reduce();
  return r3;
}

Rational operator*(const Rational& r1, const Rational& r2){
  Rational r3(r1.getNumerator() *r2.getNumerator(), r1.getDenominator()*r2.getDenominator());
  r3.reduce();
  return r3;
}

Rational operator/(const Rational& r1, const Rational& r2){
  Rational r3(r1.getNumerator()*r2.getDenominator(), r1.getDenominator()* r2.getNumerator());
  r3.reduce();
  return r3;
}

bool operator==(const Rational& r1, const Rational& r2){
  return(r1.getNumerator() == r2.getNumerator() && r1.getDenominator() == r2.getDenominator());
}

bool operator<=(const Rational& r1, const Rational& r2){
  return((r1.getNumerator()*r2.getDenominator()) <= (r2.getNumerator()*r1.getDenominator()));
}

bool operator>=(const Rational& r1, const Rational& r2){
  return((r1.getNumerator()*r2.getDenominator()) >= (r2.getNumerator()*r1.getDenominator()));
}

bool operator<(const Rational& r1, const Rational& r2){
  return((r1.getNumerator()*r2.getDenominator()) < (r2.getNumerator()*r1.getDenominator()));
}

bool operator>(const Rational& r1, const Rational& r2){
  return(r1.getNumerator()*r2.getDenominator() > r2.getNumerator()*r1.getDenominator());
}


//////////////////////////////////////////////////////////////////
//ARITHMETIC AND BOOLEAN OPERATORS FOR A RATIONAL AND AN INTEGER//
//////////////////////////////////////////////////////////////////

Rational operator+(const Rational& r1, int i){
  Rational r3((i*r1.getDenominator()+r1.getNumerator()), r1.getDenominator());
  r3.reduce();
  return r3;
}

Rational operator-(const Rational& r1, int i){
  Rational r3((r1.getNumerator()-i*r1.getDenominator()), r1.getDenominator());
  r3.reduce();
  return r3;
}

Rational operator*(const Rational& r1, int i){
  Rational r3(r1.getNumerator()*i, r1.getDenominator());
  r3.reduce();
  return r3;
}

Rational operator/(const Rational& r1, int i){
  Rational r3(r1.getNumerator(), r1.getDenominator()*i);
  r3.reduce();
  return r3;
}

bool operator==(const Rational& r1, int i){
  return (r1.getDenominator() == 1 && r1.getNumerator() == i);
}

bool operator<=(const Rational& r1, int i){
  return( r1.getNumerator() <= i*r1.getDenominator() );
}

bool operator>=(const Rational& r1, int i){
  return( r1.getNumerator() >= i*r1.getDenominator() );
}

bool operator<(const Rational& r1, int i){
  return( r1.getNumerator() < i*r1.getDenominator() );
}

bool operator>(const Rational& r1, int i){
  return( r1.getNumerator() > i*r1.getDenominator() );
}


/////////
//OTHER//
/////////

std::ostream& operator<<(std::ostream & outStream, const Rational& r){
  if(r.getDenominator() == 1){
    outStream << r.getNumerator();
  }
  else{
    outStream << r.getNumerator() << "/" << r.getDenominator();
  }
  return outStream;
}

int gcd(int a, int b){
  if(b == 0){
    return a;
  }
  else{
    return gcd(b, a%b);
  }
}
