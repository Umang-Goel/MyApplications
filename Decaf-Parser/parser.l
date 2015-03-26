%{
#include "AST.h"
#include <bits/stdc++.h>
using namespace std;
#include "parser.tab.hpp"

#define GET_TOKEN yylval.str = new string(yytext, strlen(yytext))
%}

%option noyywrap

%%

return {return RET;}
break {return BREAK;}
Program {return PROGRAM;}
continue {return CONT;}
class {return CLASS;}
callout {return CALLOUT;}

"{" {return OPEN;}
"}" {return CLOSE;}
"[" {return SQOPEN;}
"]" {return SQCLOSE;}
"(" {return ROPEN;}
")" {return RCLOSE;}
"," {return COMMA;}
";" {return END;}

int|boolean {GET_TOKEN; return TYPE;}
void {GET_TOKEN; return VOID;}

if {return IF;}
else {return ELSE;}
for {return FOR;}

"+" {GET_TOKEN; return PLUS;}
"-" {GET_TOKEN; return MINUS;}
[*\/] {GET_TOKEN; return MULT_DIV;}
&&|\|\| {GET_TOKEN; return CONDOP;}
==|!= {GET_TOKEN; return EQOP;}
\<|\<=|\>=|\> {GET_TOKEN; return RELOP;}
\=|\+\=|\-\= {GET_TOKEN; return ASOP;}
"!" {GET_TOKEN; return NOTOP;}

\/\/.*\n {}
[ \t\n]* {}

true|false {GET_TOKEN; return BOOLVAL;}
[A-Za-z][A-Za-z0-9]* {GET_TOKEN; return ID;}
[0-9]+ {GET_TOKEN; return INTLIT;}
0x[0-9a-fA-F]+ {GET_TOKEN; return HEXLIT;}
'[a-zA-z]' {GET_TOKEN; return CHARLIT;}
\"[a-zA-z]*\" {GET_TOKEN; return STRLIT;}

%%
