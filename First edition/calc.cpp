// calc.cpp
#include "calc.h"

#include <cctype>

#include <iostream>
#include <map>
#include <string>

using namespace std;

// error function
int no_of_errors;

double error(const string& s)
{
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}
// END error function

Token_value curr_tok = PRINT;

double expr(bool get)
{
    double left = term(get);

    for (;;)
    {
        switch (curr_tok) {
            case PLUS:
                left += term(true);
                break;
            case MINUS:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

double term(bool get)
{
    double left = prim(get);

    for (;;)
    {
        switch (curr_tok) {
            case MUL:
                left *= prim(true);
                break;
            case DIV:
                if (double d = prim(true)) {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

double number_value;
string string_value;
map<string, double> table;   // var table

double prim(bool get)
{
    if (get) get_token();

    switch (curr_tok) {
        case NUMBER:
        {   double v = number_value;
            get_token();
            return v;
        }
        case NAME:
        {   double& v = table[string_value];
            if (get_token() == ASSIGN) v = expr(true);
            return v;
        }
        case MINUS:
            return -prim(true);
        case LP:
        {   double e = expr(true);
            if (curr_tok != RP) return error(") expected");
            get_token();
            return e;
        }
        default:
            return error("primary expected");
    }
}

// --BEGIN-- OPTIMIZE get_token function
// Token_value get_token()
// {
//     char ch = 0;
//     cin >> ch;
//
//     switch (ch) {
//         case 0:
//             return curr_tok = END;   // assign and return
//         case ';':
//         case '*':
//         case '/':
//         case '+':
//         case '-':
//         case '(':
//         case ')':
//         case '=':
//             return curr_tok = Token_value(ch);
//         case '0': case '1': case '2': case '3': case '4':
//         case '5': case '6': case '7': case '8': case '9':
//         case '.':
//             cin.putback(ch);
//             cin >> number_value;
//             return curr_tok = NUMBER;
//         default:
//             if (isalpha(ch)) {
//                 cin.putback(ch);
//                 cin >> string_value;
//                 return curr_tok = NAME;
//             }
//             error("bad token");
//             return curr_tok = PRINT;
//     }
// }

Token_value get_token()
{
    char ch = 0;

    // --BEGIN-- ignore blanks except '\n'
    // do {
    //     if (!cin.get(ch)) return curr_tok = END;
    // } while (ch != '\n' && isspace(ch));
    cin >> ch;
    // ---END--- ignore blanks except '\n'

    switch (ch) {
        case 0:
            return curr_tok = END;   // assign and return
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok = Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            cin.putback(ch);
            cin >> number_value;
            return curr_tok = NUMBER;
        default:
            if (isalpha(ch)) {
                // --BEGIN-- Optimize to avoid meeting blank issue
                // cin.putback(ch);
                // cin >> string_value;
                string_value = ch;
                while (cin.get(ch) && isalnum(ch)) string_value.push_back(ch);
                cin.putback(ch);
                // ---END_-- Optimize to avoid meeting blank issue
                return curr_tok = NAME;
            }
            error("bad token");
            return curr_tok = PRINT;
    }
}
// ---END--- OPTIMIZE get_token function

