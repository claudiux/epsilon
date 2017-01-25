#include <poincare/symbol.h>
#include <poincare/context.h>
#include <math.h>
#include "layout/string_layout.h"
extern "C" {
#include <assert.h>
}

Symbol::Symbol(char name) :
  m_name(name)
{
}

float Symbol::approximate(Context& context) const {
  if (context.expressionForSymbol(this)) {
    return context.expressionForSymbol(this)->approximate(context);
  }
  // TODO: decide with Leo what we should return
  return NAN;
}

Expression * Symbol::evaluate(Context& context) const {
  return context.expressionForSymbol(this)->evaluate(context);
}

Expression::Type Symbol::type() const {
  return Expression::Type::Symbol;
}

const char Symbol::name() const {
  return m_name;
}

ExpressionLayout * Symbol::createLayout() const {
  if (m_name == SpecialSymbols::Ans) {
    return new StringLayout("ans", 4);
  }
  return new StringLayout(&m_name, 1);
}

Expression * Symbol::clone() const {
  return new Symbol(m_name);
}

bool Symbol::valueEquals(const Expression * e) const {
  assert(e->type() == Expression::Type::Symbol);
  return (m_name == ((Symbol *)e)->m_name);
}
