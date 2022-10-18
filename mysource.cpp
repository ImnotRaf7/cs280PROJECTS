//
// Created by Rafa on 10/17/2022.
//
#include "lex.h"
#include <iterator>



ostream& operator<<(ostream& out, const LexItem& tok){

}
LexItem id_or_kw(const string& lexeme, int linenum){
    //define if the lexeme is a keyword or identifier

    //KEYWORDS TO CHECK UP

    //we are being passed a lexeme --- (la suma de los char hasta que encuenrtre un espacio) o iterar por palabras
    map<string,Token> :: iterator my_it;
    map<string,Token> kwmap = {
            { "PROGRAM", PROGRAM},
            { "PRINT", PRINT},
            { "INT", INT},
            { "END", END },
            { "FLOAT", FLOAT},
            { "ELSE", ELSE },
            { "IF", IF },
            { "THEN", THEN},
            { "TRUE", TRUE},
            { "FALSE", FALSE},
            { "BOOL", BOOL }
    };
    for(my_it=kwmap.begin();my_it!=kwmap.end();my_it++){
        if(lexeme == my_it->first){
            return LexItem(my_it->second,lexeme,linenum);
        }
        return LexItem(IDENT,lexeme,linenum);
    }


}




LexItem getNextToken(istream& in, int& linenum){

    // recognizes the type of token that is being passed down  "char" and the line num

    /** keywords are treated as identifiers,however if its a keyword we return its name not (IDENT), if this is and identfitier then we just return the default
     *       check cases for BOOLEAN keywords
     *
     *
     *
     * we have to check the lenght of the token that we are dealing with:
     * one char tokens means that the next char is a space
     * two char+ tokens means that the next char is not a space. peek()
     * if in is (+, -, *, /, =, <, >, :) it means they are single lined tokens;
     *              return the lexeme
     *
     *
     *
     *
     *
     *  when defining the states we use enum type
     *
     *
     *
     *
     */

    //returns a  lex item
    //its getting each token
}
