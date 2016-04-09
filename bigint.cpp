// $Id: bigint.cpp,v 1.74 2016-03-24 19:30:57-07 - - $

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

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)

}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
		//vector_size = uvalue.get_vector_size();
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0)); 
   vector_size = uvalue.get_vector_size();
}






bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}


bigint bigint::operator+ (const bigint& that) const {
   ubigint ubig_result;
   bigint final_result;
   // test
   //cout << "first bigint value: " << uvalue << endl;
   cout << "second bigint value: " << that.uvalue << endl;
   
   // If signs are the same... 
   if ((is_negative == that.is_negative)) { 
	ubig_result = uvalue + that.uvalue; 
        final_result.is_negative = is_negative;
	//cout << "test... hit in bigint add signs the same.. " << endl;
   }
 
   else { // ... Else, signs are different ... 
	if (uvalue > that.uvalue ){
		final_result.is_negative = is_negative; 
		ubig_result = uvalue - that.uvalue;	
	} else if (uvalue < that.uvalue ) {
		final_result.is_negative = that.is_negative;
		
		ubig_result = that.uvalue - uvalue;	
	}
   }
   final_result.uvalue = ubig_result;
   
   //else if different, call - operator.
   return final_result;
}

bigint bigint::operator- (const bigint& that) const {
   ubigint result = uvalue - that.uvalue;
   return result;
}

bigint bigint::operator* (const bigint& that) const {
   bigint result;
   if (not(is_negative == that.is_negative)){
	result.is_negative = true; // - * + = -
   } else if (is_negative == true){ ///signs are the same and both -
   	result.is_negative = false; // resulting sign is positive
   } else { result.is_negative = false; } // otherwise is +;
   result. uvalue = uvalue * that.uvalue;
   return result;
}

bigint bigint::operator/ (const bigint& that) const {
   bigint result = uvalue / that.uvalue;
   return result;
}

bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

bool bigint::operator== (const bigint& that) const{
   
   if (not((is_negative == that.is_negative) and (vector_size == that.vector_size))){
		return false;
   }
   if (not(uvalue == that.uvalue)) { //difference found 
		return false; //bigints not the same
   }
   // else ... 
   return true; 
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   return out << "bigint(" << (that.is_negative ? "'-'" : "'+'")
              << that.uvalue << ")";
}

