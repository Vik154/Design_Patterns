/* Паттерн Интерпретатор (Interpreter) */
// Концепция - https://www.programmersought.com/article/48174177870/
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns/Behavioral_Patterns#Interpreter

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>

// Концепция паттерна "Интерпретатор"
namespace InterpreterСoncept {

    class Context {
    public:
        Context()  { }
        ~Context() { }
    };

    class AbstractExpression abstract {
    public:
        virtual ~AbstractExpression() {}
        virtual void Interpret(const Context& c) = 0;
    protected:
        AbstractExpression() {}
    };

    class TerminalExpression : public AbstractExpression {
    public:
        ~TerminalExpression() {}
        TerminalExpression(const std::string& statement) : _statement(statement) {};
        
        void Interpret(const Context& c) override {
            std::cout << _statement << " TerminalExpression\n";
        }
    private:
        std::string _statement;
    };

    class NonterminalExpression : public AbstractExpression {
    public:
        NonterminalExpression(AbstractExpression* expression, int times) :
            _expression(expression), _times(times) 
        { }
        
        ~NonterminalExpression() {
            _expression = nullptr;
        }

        void Interpret(const Context& c) override {
            for (int i = 0; i < _times; i++)
                _expression->Interpret(c);
        }
    private:
        AbstractExpression* _expression = nullptr;
        int _times;
    };

    int run() {
        Context* c = new Context();
        AbstractExpression* te = new TerminalExpression("hello");
        AbstractExpression* nte = new NonterminalExpression(te, 2);
        nte->Interpret(*c);
        delete c;
        delete te;
        delete nte;
        return 0;
    }
}


//--------------------------------------------------------------
// Реализация паттерна "Интерпретатор"
//--------------------------------------------------------------
namespace Behavioral {
    using std::string;
    using std::map;
    using std::list;


    struct Expression {
        virtual int interpret(map<string, Expression*> variables) = 0;
        virtual ~Expression() {}
    };

    class Number : public Expression {
    private:
        int number;
    public:
        Number(int number) : number(number) {};
        int interpret(map<string, Expression*> variables) { return number; }
    };

    class Plus : public Expression {
        Expression* leftOperand;
        Expression* rightOperand;
    public:
        Plus(Expression* left, Expression* right) {
            leftOperand = left;
            rightOperand = right;
        }
        ~Plus() {
            delete leftOperand;
            delete rightOperand;
        }

        int interpret(map<string, Expression*> variables) {
            return leftOperand->interpret(variables) + rightOperand->interpret(variables);
        }
    };

    class Minus : public Expression {
        Expression* leftOperand;
        Expression* rightOperand;
    public:
        Minus(Expression* left, Expression* right) {
            leftOperand = left;
            rightOperand = right;
        }
        ~Minus() {
            delete leftOperand;
            delete rightOperand;
        }

        int interpret(map<string, Expression*> variables) {
            return leftOperand->interpret(variables) - rightOperand->interpret(variables);
        }
    };

    class Variable : public Expression {
        string name;
    public:
        Variable(string name) : name(name) {};
        int interpret(map<string, Expression*> variables) {
            if (variables.end() == variables.find(name)) return 0;
            return variables[name]->interpret(variables);
        }
    };

    class Evaluator : public Expression {
        Expression* syntaxTree;
    public:
        Evaluator(string expression) {
            list<Expression*> expressionStack;
            size_t last = 0;

            for (size_t next = 0; string::npos != last; 
                last = (string::npos == next) ? next : (1 + next)) {

                next = expression.find(' ', last);
                string token(expression.substr(last, (string::npos == next) ? 
                    (expression.length() - last) : (next - last)));

                if (token == "+") {
                    Expression* right = expressionStack.back(); 
                    expressionStack.pop_back();
                    Expression* left = expressionStack.back(); 
                    expressionStack.pop_back();
                    Expression* subExpression = new Plus(right, left);
                    expressionStack.push_back(subExpression);
                }
                else if (token == "-") {
                    Expression* right = expressionStack.back(); 
                    expressionStack.pop_back();
                    Expression* left = expressionStack.back(); 
                    expressionStack.pop_back();
                    Expression* subExpression = new Minus(left, right);
                    expressionStack.push_back(subExpression);
                }
                else
                    expressionStack.push_back(new Variable(token));
            }
            syntaxTree = expressionStack.back(); expressionStack.pop_back();
        }

        ~Evaluator() {
            delete syntaxTree;
        }

        int interpret(map<string, Expression*> context) {
            return syntaxTree->interpret(context);
        }
    };

    void test_interpreter() {

        Evaluator sentence("w x z - +");
        static const int sequences[][3] = {
                {5, 10, 42}, {1, 3, 2}, {7, 9, -5},
        };

        for (size_t i = 0; sizeof(sequences) / sizeof(sequences[0]) > i; ++i) {
            map<string, Expression*> variables;
            variables["w"] = new Number(sequences[i][0]);
            variables["x"] = new Number(sequences[i][1]);
            variables["z"] = new Number(sequences[i][2]);
            int result = sentence.interpret(variables);
            for (map<string, Expression*>::iterator it = variables.begin(); variables.end() != it; ++it) 
                delete it->second;
            std::cout << "Interpreter result: " << result << std::endl;
        }
    }
}