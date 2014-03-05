////////////////////////////////////
// init.h
// initialization of this program
////////////////////////////////////

// definitions for this program
#define PROGNAME "Reverse Lang"
#define PROGVER  "20130119 testing"
#define INPUTSTR "Input > "

// required C++ headers
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream> // ltoa, ftoa
#include <list>
#include <cmath>

// headers for this program
// note: these headers may need to be put in correct order. be careful.
#include "typeenum.h"  // required by "element.h", "strfunc.h"
#include "strfunc.h"   // required by "interpret.h"
#include "element.h"   // required by "strfunc.h"
#include "interpret.h" // required by "main.cpp"

// DEBUG : when you execute this program, it will show you several debug messages.
//         if you comment out line below this, debug will be enabled.
// #define DEBUG
