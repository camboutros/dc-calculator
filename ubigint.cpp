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
   printable_value = {}; // fix
   unsigned char push_char;
   int work_num;
   while (that > 0 ) {
  	 work_num = that % 10;
 	 push_char  = 10 - work_num;
  	 that = that / 10;
	 ubig_value.push_back(push_char);
   }
   u_vector_size = ubig_value.size(); // init u_vector_size
}

ubigint::ubigint (const string& that): ubig_value(0) {


  /////////// Initialize Container //////////////
  for(auto ritor = that.crbegin(); ritor != that.crend(); ++ritor){
	ubig_value.push_back(*ritor);
       
   //cout << "current digit = " << *ritor << endl;//test
   printable_value.push_back(to_string((*ritor - '0' )));
  }
  //cout << "current printable_value in constructor: " << *this << endl; // test
  /////////// Trim Trailing Zeros ///////////////
  while (ubig_value.size() > 0 and ubig_value.back() == 0 )   ubig_value.pop_back();  

  /// Set printable_value ... ///////////////////
  // printable_value  //lazy way

  /// Set Vector Size ////////////////////
  u_vector_size = ubig_value.size();
}

ubigint ubigint::operator+ (const ubigint& that) const {
   auto u_itor = ubig_value.cbegin();
   auto u_titor = that.ubig_value.cbegin();
   int carry = 0;
   udigit_t sum_char;
   ubigint result;
   
   while(u_itor != ubig_value.end() and u_titor != that.ubig_value.end()) {
	sum_char = (*u_itor + *u_titor - '0'); //converted down for arithmetic
	//cout << sum_char << " initial sum_char value ... " << endl; //test
	
		if(carry == 1) {
			cout << "hit carry" << endl; //test
			sum_char = sum_char + '1' - '0';
			carry = 0; // reset carry
		}
		if ((sum_char) > 57) { // '57' is ASCII for '9'
			cout << "hit sum > 9" << endl; //test
			sum_char = sum_char - 10;
			sum_char = sum_char + 0;
			carry = 1; // set carry
		}
	result.ubig_value.push_back((sum_char - '0'));
	
	++u_itor;
	++u_titor;
	}
   if (carry == 1 ) {
	result.ubig_value.push_back('1' - '0');
        cout << "storing carry: " << ('1' - '0') << endl; //test
   }
  
    ///////////// ... In the event that one arg is longer than the other... //////////	
    while(u_itor != ubig_value.end()){
	result.ubig_value.push_back((*u_itor - '0'));
	++u_itor;
   }
	 
   while(u_titor != that.ubig_value.end()){
	result.ubig_value.push_back((*u_titor - '0'));
	++u_titor;
   }
   /////////////////////////////////////////////////

   ///// Make a printable version of ubigint result.... /////////
   udigit_t holdchar;
   
   auto ritor = result.ubig_value.cbegin();
   while (ritor != result.ubig_value.cend()){
	holdchar = *ritor;
	result.printable_value.push_back( to_string(holdchar));
	//cout << (*ritor + 0 ) << " test ritor value  " << endl; // test 
	ritor++;
   }

   //////////////////////////////////////////////////////////////
	
   return result; //check; does this work?
}

ubigint ubigint::operator- (const ubigint& that) const {
   auto u_itor = ubig_value.cbegin();
   auto u_titor = that.ubig_value.cbegin();
   int borrow = 0;
   udigit_t diff_char;
   ubigint result;

  while(u_itor != ubig_value.end() and u_titor != that.ubig_value.end()) {
	if (*u_itor < *u_titor){ // set carry 
		borrow = -1;
		diff_char = (*u_itor + 10);
	}  
		diff_char = (*u_itor - *u_titor);
		if(borrow == 1) {
			diff_char = diff_char - 1;
			borrow = 0; // reset carry
		}
		
	result.ubig_value.push_back(diff_char);
	++u_itor;
	++u_titor;

	}
   if (borrow == -1 ) {
	cout << "WARNING: CARRY OVERFLOW" << endl; //fix later
   }

 ///////////// ... In the event that one arg is longer than the other... //////////	
    while(u_itor != ubig_value.end()){
	result.ubig_value.push_back((*u_itor - '0'));
	++u_itor;
   }
	 
   while(u_titor != that.ubig_value.end()){
	result.ubig_value.push_back((*u_titor - '0'));
	++u_titor;
   }
   /////////////////////////////////////////////////

 ///// Make a printable version of ubigint result.... /////////
   udigit_t holdchar;
   auto ritor = result.ubig_value.cbegin();
   while (ritor != result.ubig_value.cend()){
	holdchar = *ritor;
	result.printable_value.push_back(to_string(holdchar));
	//cout << (*ritor - 0) << " test ritor value in +  " << endl; // test change later; working in offset
        //cout << result.printable_value << " test printable_value  " << endl; // test
	ritor++;
   }

   //////////////////////////////////////////////////////////////
	
  

   return result; // test
}

ubigint ubigint::operator* (const ubigint& that) const {
   ubigint product; 
   
   product.ubig_value[u_vector_size + that.u_vector_size]; // inits vector to sum of sizes 
   int base_place = 0;
   udigit_t store_char;
   //udigit_t temp;
   int carry = 0;
   int sum;
   
   
   for (auto i = ubig_value.cbegin(); i != ubig_value.cend(); i++){
	
	for (auto j = that.ubig_value.cbegin(); j != that.ubig_value.cend(); j++){
	
		sum = ((*i - '0') * ( *j - '0')) + carry;
		if (sum > 9){
			 store_char = ((10 -((*i * *j) % 10) ) + '0');
                         carry = ((*i * *j)/ 10);
			  product.ubig_value.insert((j + base_place),( store_char + '0')); // fix

			 
			if (j == (that.ubig_value.cend() - 1)){
				product.ubig_value.push_back(carry + '0');
			}
		} else {
			carry = 0; // reset carry 
			store_char = sum + '0';
			product.ubig_value.insert((j + base_place),( store_char + '0')); // fix
		}
			 
	}
	base_place = base_place + 1;
   }
	
   return product; // test
}

void ubigint::multiply_by_2() {
   //udigit_t store_char;
   //char carry = 0;
   //for (auto i = ubig_value.cbegin(); i != ubig_value.cend(); i++){
        
   //	if ((((*i * 2) + carry) > 9 )){ // make sure types add up
   //		store_char = ((*i * 2) - 10);
   //		carry = 1;
   //		ubig_value.at(i) = store_char; // check syntax
   //	} 
   // fix/test	 
}

void ubigint::divide_by_2() {
   //uvalue /= 2; test
}

int ubigint::get_vector_size() {
	return u_vector_size;
}



struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, ubigint divisor) {
   // Note: divisor is modified so pass by value (copy).
   ubigint zero {'0'};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {'1'};
   ubigint quotient {'0'};
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
   auto u_itor = ubig_value.cbegin();
   auto u_titor = that.ubig_value.cbegin();
   while(u_itor != ubig_value.end() and u_titor != that.ubig_value.end()) {
	if (*u_itor != *u_titor){
		return false;
	} // else... 
        ++u_itor;
	++u_titor;  
    }
    return true;
}

bool ubigint::operator< (const ubigint& that) const {
   auto u_itor = ubig_value.crbegin();
   auto u_titor = that.ubig_value.crbegin();
   while(u_itor != ubig_value.crend() and u_titor != that.ubig_value.crend()) {
	if (*u_itor > *u_titor){
		return false;
	} // else... 
        ++u_itor;
	++u_titor;  
    }
    return true; // test
}

ostream& operator<< (ostream& out, const ubigint& that) { 
  string printable;
  for (auto i = that.printable_value.rbegin(); i != that.printable_value.rend(); i++){
  	printable = printable.append( *i);
    }
   return out << printable; 
}

