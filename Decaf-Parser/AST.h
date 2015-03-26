#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>
using namespace std;

inline void ptabs(int tabs)
{
    for (int i = 0; i < tabs; ++i) {
        cout << "    ";
    }
}

class ASTNode;
class ASTProgram;
class ASTDecl;
class ASTVarDecl;
class ASTMethodDecl;
class ASTBlock;
class ASTStatement;
class ASTAssignment;
class ASTLocation;
class ASTLocation1;
class ASTLocation2;
class ASTMethodCall;
class ASTMethodCall1;
class ASTMethodCall2;
class ASTCalloutArgs;
class ASTCalloutArgs1;
class ASTCalloutArgs2;
class ASTIf;
class ASTFor;
class ASTReturn;
class ASTContinue;
class ASTBreak;
class ASTExpr;
class ASTLiteral;
class ASTLiteralInt;
class ASTLiteralString;
class ASTLiteralBool;
class ASTBinopExpr;
class ASTUnaryExpr;


class ASTNode
{
    public:
        ASTNode(){};
};

class ASTDecl: public ASTNode
{
    public:
        ASTDecl() {}
        virtual void print_ast(int tabs) {}
};

class ASTProgram: public ASTNode
{
    private:
        vector<ASTDecl*> *decl_;
    public:
        ASTProgram(vector<ASTDecl*> *decl)
        {
            decl_ = decl;
        }
        void print_ast(int tabs)
        {
            cout << " --- Program Starts --- " << endl;
            vector<ASTDecl*> d = *decl_;
            for (int i = 0; i < d.size(); ++i) {
		if(d[i] != NULL)
	                d[i]->print_ast(tabs + 1);
            }
        }
};


class ASTVar: public ASTNode
{
    public:
        ASTVar() {}
        virtual void print_ast(int tabs) {}
};

class ASTVar1: public ASTVar
{
    private:
        string *var_;
    public:
        ASTVar1(string *var)
        {
            var_ = var;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << *var_ << endl;
        }
};

class ASTVar2: public ASTVar
{
    private:
        string *var_;
        string *len_;
    public:
        ASTVar2(string *var, string *len)
        {
            var_ = var;
            len_ = len;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << *var_ << "[" << *len_ << "]\n";
        }
};

class ASTVarDecl: public ASTDecl
{
    private:
        vector< pair<string*, ASTVar*> > *var_list_;
    public:
        ASTVarDecl() {}
        ASTVarDecl(vector< pair<string*, ASTVar*> > *var_list)
        {
            var_list_ = var_list;
        }
        void add_vars(pair<string*, ASTVar*> var)
        {
            if (var_list_ == NULL) {
                var_list_ = new vector< pair<string*, ASTVar*> >;
            }
            var_list_->push_back(var);
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "--- Field decl ---" << endl;
            vector< pair<string*, ASTVar*> > v = *var_list_;
            for (int i = 0; i < v.size(); ++i)
            {
                ptabs(tabs);
                cout << *(v[i].first) << " ";
                v[i].second->print_ast(0);
            }
            ptabs(tabs);
            cout << "--- ----- ---- ---" << endl;
        }
};

class ASTStatement: public ASTNode
{
    public:
        ASTStatement() {}
        virtual void print_ast(int tabs) {}
};

class ASTBlock: public ASTStatement
{
    private:
        ASTVarDecl *vars_;
        vector<ASTStatement*> *statements_;
    public:
        ASTBlock(ASTVarDecl *vars, vector<ASTStatement*> *statements)
        {
            vars_ = vars;
            statements_ = statements;
        }
        void print_ast(int tabs)
        {
            if (vars_ != NULL)
            {
                vars_->print_ast(tabs);
                cout << endl;
            }
            vector<ASTStatement*> s = *statements_;
            for (int i = 0; i < s.size(); ++i)
            {
                s[i]->print_ast(tabs);
            }
        }
};

class ASTExpr: public ASTNode
{
    public:
        ASTExpr() {}
        virtual void print_ast(int tabs) {}
};

class ASTLocation: public ASTExpr, public ASTStatement
{
    public:
        ASTLocation() {}
        virtual void print_ast(int tabs) {}
};

class ASTAssignment: public ASTStatement
{
    private:
        ASTLocation *loc_;
 //       string *op_;
        ASTExpr *expr_;
    public:
        ASTAssignment(ASTLocation *loc, ASTExpr *expr)
        {
            loc_ = loc;
   //         op_ = op;
            expr_ = expr;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Assignment:" << endl;
            ptabs(tabs+1);
            cout << "lhs:\n"; loc_->print_ast(tabs+2);
       //     ptabs(tabs+1);
     //       cout << "Op: " << *op_ << endl;
            ptabs(tabs+1);
            cout << "rhs: \n"; expr_->print_ast(tabs+2); 
        }
};

class ASTLocation1: public ASTLocation
{
    private:
        string *id_;
    public:
        ASTLocation1(string *id)
        {
            id_ = id;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Variable:" << endl;
            ptabs(tabs+1);
            cout << *id_ << endl;
        }
};

class ASTLocation2: public ASTLocation
{
    private:
        string *id_;
        ASTExpr *expr_;
    public:
        ASTLocation2(string *id, ASTExpr *expr)
        {
            id_ = id;
            expr_ = expr;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Array:" << endl;
            ptabs(tabs+1);
            cout << *id_ << endl;; 
            ptabs(tabs+1);
            cout << "Index\n";
            expr_->print_ast(tabs+2);
        }
};

class ASTMethodCall: public ASTStatement, public ASTExpr
{
    public:
        ASTMethodCall() {}
};

class ASTMethodCall1: public ASTMethodCall
{
    private:
        string *id_;
        vector<ASTExpr*> *expr_;
    public:
        ASTMethodCall1(string *id, vector<ASTExpr*> *expr)
        {
            id_ = id;
            expr_ = expr;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Method call:\n";
            ptabs(tabs+1);
            cout << "Name: " << *id_ << endl;
            ptabs(tabs+1);
            cout << "Args:\n";
            vector<ASTExpr*> e = *expr_;
            for (int i = 0; i < e.size(); ++i)
            {
                e[i]->print_ast(tabs+2);
            }
        }

};

class ASTCalloutArgs
{
    public:
        ASTCalloutArgs() {}
        virtual void print_ast(int tabs) {}
};

// A.K.A callout
class ASTMethodCall2: public ASTMethodCall
{
    private:
        string *name_;
        vector<ASTCalloutArgs*> *cargs_;
    public:
        ASTMethodCall2(string *name, vector<ASTCalloutArgs*> *cargs)
        {
            name_ = name;
            cargs_ = cargs;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Callout\n";
            ptabs(tabs+1);
            cout << "Name: " << *name_ << endl;
            ptabs(tabs+1);
            cout << "Args:\n";
            vector<ASTCalloutArgs*> c = *cargs_;
            for (int i = 0; i < c.size(); ++i)
            {
                c[i]->print_ast(tabs+2);
            }
        }
};

class ASTCalloutArgs1: public ASTCalloutArgs
{
    private:
        ASTExpr *expr_;
    public:
        ASTCalloutArgs1(ASTExpr *expr)
        {
            expr_ = expr;
        }
        void print_ast(int tabs)
        {
	    if(expr_ != NULL)
	            expr_->print_ast(tabs);
        }
};

class ASTCalloutArgs2: public ASTCalloutArgs
{
    private:
        string *id_;
    public:
        ASTCalloutArgs2(string *id)
        {
            id_ = id;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << *id_ << endl;
        }
};


class ASTIf: public ASTStatement
{
    private:
        ASTExpr *expr_;
        ASTBlock *ifblock_, *elseblock_;
    public:
        ASTIf(ASTExpr *expr, ASTBlock *ifblock, ASTBlock *elseblock)
        {
            expr_ = expr;
            ifblock_ = ifblock;
            elseblock_ = elseblock;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "If:\n";
            ptabs(tabs+1);
            cout << "Cond:\n";
            expr_->print_ast(tabs+2);
	    if(ifblock_ != NULL)
	    {
		    ptabs(tabs+1);
		    cout << "Ifblock:\n";
		    ifblock_->print_ast(tabs+2);
	    }
	    if(ifblock_ != NULL)
	    {
		    ptabs(tabs+1);
		    cout << "Elseblock:\n";
		    elseblock_->print_ast(tabs+2);
	    }
        }
};

class ASTFor: public ASTStatement
{
    private:
        string *id_;
        ASTExpr *expr1_;
        ASTExpr *expr2_;
        ASTBlock *block_;
    public:
        ASTFor(string *id, ASTExpr *expr1, ASTExpr *expr2, ASTBlock *block)
        {
            id_ = id;
            expr1_ = expr1;
            expr2_ = expr2;
            block_ = block;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "For:\n";
            ptabs(tabs+1);
            cout << "Init:\n";
            ptabs(tabs+2);
            cout << "lhs: " << *id_ << endl;

            ptabs(tabs+2);
            cout << "rhs: \n";
	    if(expr1_ != NULL)
	            expr1_->print_ast(tabs+3);

            ptabs(tabs+1);
            cout << "Cond:\n";
	    if(expr2_ != NULL)
	            expr2_->print_ast(tabs+2);

            ptabs(tabs+1);
            cout << "Block:\n";
	    if(block_ != NULL)
	            block_->print_ast(tabs+2);
        }
};

class ASTReturn: public ASTStatement
{
    private:
        ASTExpr *expr_;
    public:
        ASTReturn(ASTExpr *expr)
        {
            expr_ = expr;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Return:" << endl;
	    if(expr_  != NULL)
	            expr_->print_ast(tabs+1);
        }
};

class ASTBreak: public ASTStatement
{
    public:
        ASTBreak() {}
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Break" << endl;
        }
};

class ASTContinue: public ASTStatement
{
    public:
        ASTContinue() {}
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Continue" << endl;
        }
};


class ASTLiteral: public ASTExpr
{
    public:
        ASTLiteral() {}
        virtual void print_ast(int tabs) {}
};

class ASTLiteralInt: public ASTLiteral
{
    private:
        string *id_;
    public:
        ASTLiteralInt(string *id)
        {
            id_ = id;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Integer: " << *id_ << endl;
        }
};

class ASTLiteralChar: public ASTLiteral
{
    private:
        string *id_;
    public:
        ASTLiteralChar(string *id)
        {
            id_ = id;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Char: " << *id_ << endl;
        }
};

class ASTLiteralBool: public ASTLiteral
{
    private:
        string *id_;
    public:
        ASTLiteralBool(string *id)
        {
            id_ = id;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Bool: " << *id_ << endl;
        }
};

class ASTBinopExpr: public ASTExpr
{
    private:
        ASTExpr *lhs_, *rhs_;
        string *op_;
    public:
        ASTBinopExpr(ASTExpr *lhs, string *op, ASTExpr *rhs)
        {
            lhs_ = lhs;
            rhs_ = rhs;
            op_ = op;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Binary expr:" << endl;
            ptabs(tabs+1);
            cout << "lhs:\n";
            lhs_->print_ast(tabs+2);
            ptabs(tabs+1);
            cout << "Op: " << *op_ << endl;
            ptabs(tabs+1);
            cout << "rhs:\n";
            rhs_->print_ast(tabs+2);
        }
};

class ASTUnaryExpr: public ASTExpr
{
    private:
        ASTExpr *expr_;
        string *op_;
    public:
        ASTUnaryExpr(ASTExpr *expr, string *op)
        {   
            expr_ = expr;
            op_ = op;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << "Unary expr:\n";
            ptabs(tabs+1);
            cout << "Operator: " << *op_ << endl;
            ptabs(tabs+1);
            cout << "Expression:\n";
            expr_->print_ast(tabs+2);
        }
};

class ASTMethodDecl: public ASTDecl
{
    private:
        string *id_, *ret_type_;
        vector< pair<string, string> > *agl_;
        ASTBlock *block_;
    public:
        ASTMethodDecl(string *ret_type, string *id, vector< pair<string, string> > *agl, ASTBlock *block)
        {
            ret_type_ = ret_type;
            id_ = id;
            agl_ = agl;
            block_ = block;
        }
        void print_ast(int tabs)
        {
            ptabs(tabs);
            cout << " --- Method Starts --- " << endl;
            
            ptabs(tabs);
            cout << "Return type: " << *ret_type_ << endl;
            
            ptabs(tabs);
            cout << "Name :" << *id_ << endl;
            
            vector< pair<string, string> > a = *agl_;
            ptabs(tabs);
            cout << "Arguments: ";
            for (int i = 0; i < a.size(); ++i)
            {
                cout << a[i].first << " " << a[i].second << ", ";
            }
            cout << endl;
            
            ptabs(tabs);
            cout << "Block: \n";
	    if(block_ != NULL)
	            block_->print_ast(tabs+1);

            ptabs(tabs);
            cout << " --- Method ends --- \n" << endl;
        }
};

#endif
