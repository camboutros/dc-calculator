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
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0)); 
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
   // If both are positive numbers...  /// 
   if ((not is_negative) and (not that.is_negative)) {
	ubig_result = uvalue + that.uvalue; 
        final_result.is_negative = is_negative;
   }
   // ...else if both are negative, add normally and adjustfor sign ///
   else if (is_negative and that.is_negative){
	ubig_result = uvalue + that.uvalue;
        final_result.is_negative = is_negative;
	 }
   else { // signs are different ... 
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
   bigint result = uvalue * that.uvalue;
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

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
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

