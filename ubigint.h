// $Id: ubigint.h,v 1.11 2016-03-24 19:43:57-07 - - $

/////////////////////////////////////
// Name: Camellia Boutros          //
// CruzID: cboutros                //
// Class: CMPS 109                 //
// Title: asg1                     //
// Date: 4/4/2016                  //
/////////////////////////////////////

#ifndef __UBIGINT_H__
#define __UBIGINT_H__

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;

#include "debug.h"
#include "relops.h"

//////////// Iterators ///////////////////
// vector<unsigned char>::const_reverse_iterator ritor; //reverse iterator //through string
//      vector<unsigned char>:: const_iterator itor; //iterator through string
//      vector<unsigned char>:: const_iterator titor; //iterator through string for temporary vector
//      vector<udigit_t>:: const_reverse_iterator u_ritor; // reverse iterator through ubig_value
//      vector<udigit_t>:: const_iterator u_itor; //iterator through ubig_value
//      vector<udigit_t>:: const_iterator u_titor; //iterator through ubig_value
//     
//////////////////////////////////////////

class ubigint {
   friend ostream& operator<< (ostream&, const ubigint&);
   private:
      using udigit_t = unsigned char;
      using ubigvalue_t = vector<udigit_t>;
       ubigvalue_t ubig_value;
      
      int u_vector_size; 
     
   public:
      vector<string> printable_value;
      void multiply_by_2();
      void divide_by_2();
      
      int get_vector_size() ;
     friend bool ubigint_check_difference_true(const ubigint&);

      ubigint() = default; // Need default ctor as well.
      ubigint (unsigned long);
      ubigint (const string&);

      ubigint operator+ (const ubigint&) const;
      ubigint operator- (const ubigint&) const;
      ubigint operator* (const ubigint&) const;
      ubigint operator/ (const ubigint&) const;
      ubigint operator% (const ubigint&) const;

      bool operator== (const ubigint&) const;
      bool operator<  (const ubigint&) const;
};

#endif

