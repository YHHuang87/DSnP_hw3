/****************************************************************************
  FileName     [ test.cpp ]
  PackageName  [ test ]
  Synopsis     [ Test program for simple database db ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2015-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "dbJson.h"

using namespace std;

extern DBJson dbjson;

class CmdParser;
CmdParser* cmdMgr = 0; // for linking purpose

int
main(int argc, char** argv)
{
   if (argc != 2) {  // testdb <jsonfile>
      cerr << "Error: using testdb <jsonfile>!!" << endl;
      exit(-1);
   }

   ifstream inf(argv[1]);

   if (!inf) {
      cerr << "Error: cannot open file \"" << argv[1] << "\"!!\n";
      exit(-1);
   }
   
   if (!dbjson == 0) {
      cout << "Table is resetting..." << endl;
      dbjson.reset();
   }
   
   if (!(inf >> dbjson)) {
      cerr << "Error in reading JSON file!!" << endl;
      exit(-1);
   }
   
   cout << "========================" << endl;
   cout << " Print JSON object" << endl;
   cout << "========================" << endl;
   cout << dbjson << endl;

   // TODO
   // Insert what you want to test here by calling DBJson's member functions
   DBJsonElem elm("Johnason",30);
   dbjson.add(elm);
   
   cout << "========================" << endl;
   cout << " Print JSON object" << endl;
   cout << "========================" << endl;
   cout << dbjson << endl << endl;

   DBJsonElem elm1("Johnasson",30);
   dbjson.add(elm1);
   
   cout << "========================" << endl;
   cout << " Print JSON object" << endl;
   cout << "========================" << endl;
   cout << dbjson << endl << endl;

   size_t pos = 0;
   cout << dbjson.sum() << ' ';
   cout << fixed << setprecision(2) << dbjson.ave() << endl;
   cout << dbjson.max(pos);
   cout.flush();
   cout << ' ' << dbjson[pos] << endl;
   cout << dbjson.min(pos);
   cout.flush();
   cout << ' ' << dbjson[pos] << endl << endl;

   struct DBSortKey k;
   struct DBSortValue v;
   dbjson.sort(k);
   cout << "========================" << endl;
   cout << " Print JSON object" << endl;
   cout << "========================" << endl;
   cout << dbjson << endl << endl;
   dbjson.sort(v);
   cout << "========================" << endl;
   cout << " Print JSON object" << endl;
   cout << "========================" << endl;
   cout << dbjson << endl << endl;

   dbjson.reset();
   cout << "========================" << endl;
   cout << " Print JSON object" << endl;
   cout << "========================" << endl;
   cout << dbjson << endl << endl;
   cout << dbjson.sum() << ' ';
   cout << fixed << setprecision(2) << dbjson.ave() << endl;
   cout << dbjson.max(pos);
   cout.flush();
   cout << ' ' << pos << endl;
   cout << dbjson.min(pos);
   cout.flush();
   cout << ' ' << pos << endl << endl;
   return 0;
}
