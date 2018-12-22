#ifndef __EXPR_H__
#define __EXPR_H__

#include <string.h>

#include "algorithm"
#include "iostream"
#include "sstream"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

class Expression
{
 protected:
  string expr;  //expString is protected for accessing from child class
  long eval;

 public:
  virtual string toString() const = 0;  //abstract class
  string getExpr() { return expr; }
  long getEval() { return eval; }
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression
{
 public:
  NumExpression(long inputNum) {
    ostringstream str1;
    str1 << inputNum;
    expr = str1.str();
    eval = inputNum;
  }

  string toString() const { return expr; }
  long evaluate() const { return eval; }
};

class OperatorExpression : public Expression
{
 protected:
  string lExpr;
  string rExpr;
  long lEval;
  long rEval;

 public:
  OperatorExpression(Expression * lhs, Expression * rhs) {
    lExpr = "(" + lhs->getExpr();
    rExpr = rhs->getExpr() + ")";
    lEval = lhs->getEval();
    rEval = rhs->getEval();
    delete lhs;
    delete rhs;
  }

  long evaluate() const { return eval; }

  string toString() const { return expr; }
};

class PlusExpression : public OperatorExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs) {
    expr = lExpr + " + " + rExpr;
    eval = lEval + rEval;
  }
};

class MinusExpression : public OperatorExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs) {
    expr = lExpr + " - " + rExpr;
    eval = lEval - rEval;
  }
};

class TimesExpression : public OperatorExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs) {
    expr = lExpr + " * " + rExpr;
    eval = lEval * rEval;
  }
};

class DivExpression : public OperatorExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs) {
    expr = lExpr + " / " + rExpr;
    eval = lEval / rEval;
  }
};
#endif
