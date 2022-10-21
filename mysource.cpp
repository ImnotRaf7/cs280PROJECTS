//
// Created by Rafa on 10/14/2022.
//
#include "lex.h"
#include "map"
#include "iterator"
map<Token,string> tokenPrint = {
        {PROGRAM, "PROGRAM"},
        {PRINT, "PRINT"},
        {INT, "INT"},
        { END, "END" },
        { FLOAT, "FLOAT"},
        { BOOL, "BOOL" },

        { ELSE, "ELSE" },
        { IF, "IF" },

        {THEN, "THEN"},
        { TRUE, "TRUE" },
        { FALSE, "FALSE" },

        { IDENT, "IDENT" },

        { ICONST, "ICONST" },
        { RCONST, "RCONST" },
        { SCONST, "SCONST" },
        { BCONST, "BCONST" },

        { PLUS, "PLUS" },
        { MINUS, "MINUS" },
        { MULT, "MULT" },
        { DIV, "DIV" },
        { ASSOP, "ASSOP" },
        { EQUAL, "EQUAL" },
        { GTHAN, "GTHAN" },
        { LTHAN, "LTHAN" },
        { AND, "AND" },
        { OR, "OR" },
        { NOT, "NOT" },

        { COMMA, "COMMA" },
        { LPAREN, "LPAREN" },
        { RPAREN, "RPAREN" },


        { SEMICOL, "SEMICOL" },

        { ERR, "ERR" },

        { DONE, "DONE" },
};
ostream& operator<<(ostream& out, const LexItem& tok){
    if(tok == IDENT){
        LexItem x = id_or_kw(tok.GetLexeme(),tok.GetLinenum());
        if(x == IDENT){

            out<< "IDENT: "<< x.GetLexeme()<<" at Line " << x.GetLinenum()<<endl;
            return out;
        }
        else{
            out<< "KEYWORD: "<< tokenPrint[x.GetToken()] << " at Line " << x.GetLinenum()<<endl;
            return out;
        }
    }
    else if (tok == ICONST|| tok==RCONST || tok == BCONST){
        out<<tokenPrint[tok.GetToken()]<<": "<< "("+tok.GetLexeme()+")"<< " at Line "<< tok.GetLinenum()<<endl;
        return out;
    }
    else if (tok == SCONST){
        out<<"SCONST: "<<"\""+tok.GetLexeme()+"\""<< " at Line "<< tok.GetLinenum()<<endl;
        return out;
    }
    else if (tok == ERR){
        out<<"Error: "<<": " << "\"" + tok.GetLexeme() + "\""<<" at Line " << tok.GetLinenum()<<endl;
        return out;

    }
    else{
        out<<tokenPrint[tok.GetToken()]+": "<<"'"+tok.GetLexeme()+"'"<< " at Line "<<tok.GetLinenum()<<endl;
        return  out;

    }


}

LexItem id_or_kw(const string& lexeme, int linenum){
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
    map<string,Token> :: iterator my_it;
    //if lexeme is in the map then return its token value and the line num;

    for(my_it=kwmap.begin(); my_it!= kwmap.end();my_it++){
        if(lexeme == my_it->first){
            return LexItem(my_it->second,lexeme,linenum);
        }


    }

    return LexItem(IDENT,lexeme,linenum);


}

LexItem getNextToken(istream &in, int &linenum)
{
    enum TokState
    {
        START, // do
        INID,
        INSTRING, 
        ININT,      
        INREAL,
        INCOMMENT // done
    } lexstate = START;
    string lexeme;
    char ch;
    while (in.get(ch))
    {
        switch (lexstate)
        {
        case START:
            if (ch == '\n')
                linenum++;
            if (isspace(ch))
                lexeme = "";
            if (ch == '+'){
                lexeme += ch;
                return LexItem(PLUS, lexeme,linenum);
            }
            else if (ch == '-')
            {
                lexeme += ch;
                return LexItem(MINUS, lexeme, linenum);
            }
            else  if (ch == '='){
                lexeme += ch;
                if(in.peek() == '='){
                    in.get(ch);
                    lexeme += ch;
                    return LexItem(EQUAL,lexeme,linenum); 
                }
                else{
                    return LexItem(ASSOP,lexeme,linenum);
                }
            }
            else if (ch == '*'){
                lexeme += ch;
                return LexItem(PLUS, lexeme,linenum);
            }
            else if (ch == '!'){
                lexeme += ch;
                return LexItem(NOT, lexeme,linenum);
            }
            else if (ch == ';')
            {
                lexeme += ch;
                return LexItem(SEMICOL, lexeme, linenum);
            }
            else if (ch == '/')
            { 
                //lexeme = /* 
                lexeme += ch;
                if (in.peek() == '*')
                {
                    in.get(ch);
                    lexeme += ch;
                    lexeme = "";
                    lexstate = INCOMMENT;
                }
                else
                {
                    return LexItem(DIV, lexeme, linenum);
                }


            }
            else if (isalpha(ch) || ch == '_'){
                    lexeme += ch;
                    if (!(isalnum(in.peek()) || in.peek() == '_' || in.peek() == '@'))
                        {
                            return LexItem(IDENT, lexeme, linenum);
                        }
                    else{
                        lexstate = INID;
                        break;
                    }
                
            }
    
            break;
        case INID:
            lexeme += ch;
            if (!(isalnum(in.peek()) || in.peek() == '_' || in.peek() == '@'))
            {
                return id_or_kw(lexeme, linenum);
            }
             break;
        case INCOMMENT:
            
            if(ch == '*'){
                if(in.peek()=='/'){
                    // lexeme += ch;
                    in.get(ch);
                   
                    // lexeme += ch;
                    lexstate = START;
                    lexeme = "";
                    break;
                }

            }
            if (ch == '\n' )
            {
                linenum++;
            }
            if (in.peek() == EOF)
            {
                lexeme += ch;
                return LexItem(ERR, lexeme, linenum);
            }
            lexeme += ch;

            break;
            
        default:
            return LexItem(ERR,"ERR",linenum);
        }

    
    }
    return LexItem(DONE, "DONE", linenum);
}