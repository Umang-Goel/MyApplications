default:
	bison -d -g -v parser.ypp
	flex parser.l
	g++ -o compiler parser.tab.cpp lex.yy.c
