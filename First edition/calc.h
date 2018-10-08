/**
 * calc.h
 *****************
 * program:
 *     END                  //END is end-of-input
 *     expr_list END
 * expr_list:
 *     expression PRINT     // PRINT is semicolon
 *     expression PRINT expr_list
 * expression:
 *     expression + term
 *     expression - term
 *     term
 * term:
 *     term / primary
 *     term * primary
 *     primary
 * primary:
 *     NUMBER
 *     NAME    // this is variable
 *     NAME = expression
 *     - primary
 *     ( expression )
 */

#ifndef CALC_H_
#define CALC_H_

#include <map>
#include <string>

using namespace std;

enum Token_value {
    NAME,       NUMBER,       END,
    PLUS='+',   MINUS='-',    MUL='*',      DIV='/',
    PRINT=';',  ASSIGN='=',   LP='(',       RP=')'
};

// for DRIVER PROGRAM
extern Token_value curr_tok;
extern map<string, double> table;   // var table
extern int no_of_errors;

extern double expr(bool get);
extern Token_value get_token();
extern double error(const string& s);
// END for DRIVER PROGRAM

extern double term(bool get);
extern double prim(bool get);

#endif
