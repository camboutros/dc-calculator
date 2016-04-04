// $Id: ubigint.cpp,v 1.11 2016-03-24 19:57:29-07 - - $

/////////////////////////////////////
// Name: Camellia Boutros          //
// CruzID: cboutros                //
// Class: CMPS 109                 //
// Title: asg1                     //
// Date: 4/4/2016                  //
/////////////////////////////////////

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"


ubigint::ubigint (unsigned long that): ubig_value (that) {
   DEBUGF ('~', this << " -> " << 5)
}

ubigint::ubigint (const string& that): ubig_value(0) {
  //vector<unsigned char>::const_reverse_iterator ritor = that.rbegin();

  /////////// Initialize Container //////////////
  for(auto ritor = that.crbegin(); ritor != that.crend(); ++ritor){
	ubig_value.push_back(*ritor - '0');
  }
  /////////// Trim Trailing Zeros ///////////////
  while (ubig_value.size() > 0 and ubig_value.back() == 0 )   ubig_value.pop_back();   
}

ubigint ubigint::operator+ (const ubigint& that) const {
   auto u_itor = ubig_value.cbegin();
   auto u_titor = that.ubig_value.cbegin();
   char carry = 0;
   udigit_t sum_char;
   ubigint result;
   
   while(u_itor != ubig_value.end() and u_titor != that.ubig_value.end()) {
	sum_char = *u_itor + *u_titor;
		if(carry == 1) {
			sum_char = sum_char + 1;
			carry = 0; // reset carry
		}
		if ((sum_char) > 9) {
			sum_char = sum_char - 10;
			carry = 1; // set carry
		}
	result.ubig_value.push_back(sum_char);// possible error - sum may be too big. If so, subtract 10.
	++u_itor;
	++u_titor;
	}
   if (carry == 1 ) {
	cout << "WARNING: CARRY OVERFLOW" << endl; //fix later
   }
  
    ///////////// ... In the event that one arg is longer than the other... //////////	
    while(u_itor != ubig_value.end()){
	result.ubig_value.push_back(*u_itor);
	++u_itor;
   }
	 
   while(u_titor != that.ubig_value.end()){
	result.ubig_value.push_back(*u_titor);
	++u_titor;
   }
   /////////////////////////////////////////////////

   return result; //check; does this work?
}

ubigint ubigint::operator- (const ubigint& that) const {
   //if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   //return ubigint (uvalue - that.uvalue);
   return that; // test
}

ubigint ubigint::operator* (const ubigint& that) const {
   //return ubigint (uvalue * that.uvalue);
   return that; // test
}

void ubigint::multiply_by_2() {
  // uvalue *= 2; test
}

void ubigint::divide_by_2() {
  // uvalue /= 2; test
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, ubigint divisor) {
   // Note: divisor is modified so pass by value (copy).
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
   //return uvalue == that.uvalue;
    return true; // test
}

bool ubigint::operator< (const ubigint& that) const {
   //return uvalue < that.uvalue;
    return true; // test
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   //return out << "ubigint(" << that.uvalue << ")";
   
   return out << "ubigint(" ")"; //test
}

