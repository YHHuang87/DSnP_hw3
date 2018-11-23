/****************************************************************************
  FileName     [ dbJson.cpp ]
  PackageName  [ db ]
  Synopsis     [ Define database Json member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2015-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <cmath>
#include <string>
#include <algorithm>
#include "dbJson.h"
#include "util.h"

using namespace std;

/*****************************************/
/*          Global Functions             */
/*****************************************/
ostream&
operator << (ostream& os, const DBJsonElem& j)
{
   os << "\"" << j._key << "\" : " << j._value;
   return os;
}

istream& operator >> (istream& is, DBJson& j)
{
   // TODO: to read in data from Json file and store them in a DB 
   // - You can assume the input file is with correct JSON file format
   // - NO NEED to handle error file format

   assert(j._obj.empty());
   string dummy;
   is>>dummy;
   if(dummy=="{")
   {
      string key_in;
      string comma;
      string colon;
      int value;
      is>>key_in;
      if(key_in[0]!='}')
      {
        do{
          is>>colon;
          is>>value;
          is>>comma;
          string key_out;
          key_out.append(key_in,1,key_in.size()-2);
          DBJsonElem temp(key_out,value);
          j._obj.push_back(temp);
          if(comma[0]!='}')is>>key_in;
        }while(comma[0]!='}');
      }
   }
   return is;
}

ostream& operator << (ostream& os, const DBJson& j)
{
   // TODO
   os << "{" << endl;
   for(int i = 0; i < j._obj.size(); i++){
   os << "  " << j._obj[i];
   if(i != j._obj.size()-1 ){
     os << ',' << endl;
   }
   else{
     os << endl << "}" << endl;
   }
  }
  if(j._obj.size() == 0){
    os << endl << "}" << endl;
  }
   return os;
}

/**********************************************/
/*   Member Functions for class DBJsonElem    */
/**********************************************/
/*****************************************/
/*   Member Functions for class DBJson   */
/*****************************************/
void
DBJson::reset()
{
   _obj.clear();
}

// return false if key is repeated
bool 
DBJson::add(const DBJsonElem& n_elem){
  for(int i=0; i<_obj.size(); i++){
    if(n_elem.key()==_obj[i].key()){
      return false;
    }
  }
  _obj.push_back(n_elem);
  return true;
}

// return NAN if DBJson is empty
float 
DBJson::ave() const{
  if(_obj.size() == 0){
    return NAN;
  }
  else{
  float s = sum();
  float num = _obj.size();
  float ans = s/num;
  return ans;
  }
}

// If DBJson is empty, set idx to size() and return INT_MIN
int 
DBJson::max(size_t& idx) const{
  if(_obj.size() == 0){
    idx = _obj.size();
    return INT_MIN;
  }
  else{
  int temp = -214783648;
  bool a = 0;
  for(int i = 0; i < _obj.size(); i++){
    if((_obj[i].value() == -214783648 && temp == _obj[i].value() && a == 0) || _obj[i].value() > temp){
      idx = i;
      temp = _obj[i].value();
      a = 1;
    }
  }
  return temp;
  }
}

// If DBJson is empty, set idx to size() and return INT_MIN
int 
DBJson::min(size_t& idx) const{
  if(_obj.size() == 0){
    idx = _obj.size();
    return INT_MIN;
  }
  int temp = 214783647;
  bool a = 0;
  for(int i = 0; i < _obj.size(); i++){
    if((_obj[i].value() == 214783647 && temp == _obj[i].value() && a == 0) || _obj[i].value() < temp){
      idx = i;
      temp = _obj[i].value();
      a = 1;
    }
  }
  return temp;
}

void
DBJson::sort(const DBSortKey& s)
{
   // Sort the data according to the order of columns in 's'
   ::sort(_obj.begin(), _obj.end(), s);
}

void
DBJson::sort(const DBSortValue& s)
{
   // Sort the data according to the order of columns in 's'
   ::sort(_obj.begin(), _obj.end(), s);
}

// return 0 if empty
int 
DBJson::sum() const{
  int s = 0;
  for(int i=0; i<_obj.size(); i++){
    s += _obj[i].value();
  }
  return s;
}
