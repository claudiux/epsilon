#include "curve_parameter_controller.h"
#include "graph_controller.h"
#include <assert.h>

using namespace Shared;

namespace Sequence {

CurveParameterController::CurveParameterController(InputEventHandlerDelegate * inputEventHandlerDelegate, GraphController * graphController, InteractiveCurveViewRange * graphRange, CurveViewCursor * cursor) :
  FunctionCurveParameterController(graphRange, cursor),
  m_goToParameterController(this, inputEventHandlerDelegate, graphRange, cursor, I18n::Message::N),
  m_sumCell(I18n::Message::TermSum),
  m_graphController(graphController)
{
}

const char * CurveParameterController::title() {
  return I18n::translate(I18n::Message::SequenceOptions);
}

bool CurveParameterController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE || (event == Ion::Events::Right && selectedRow() == 1)) {
    switch (selectedRow()) {
      case 0:
      {
        StackViewController * stack = (StackViewController *)parentResponder();
        stack->pop();
        stack->push(m_graphController->termSumController());
        return true;
      }
      case 1:
        return handleGotoSelection();
      default:
        return false;
    }
  }
  return false;
}

int CurveParameterController::numberOfRows() {
  return k_totalNumberOfCells;
};

HighlightCell * CurveParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCells);
  HighlightCell * cells[] = {&m_sumCell, &m_goToCell};
  return cells[index];
}

int CurveParameterController::reusableCellCount() {
  return k_totalNumberOfCells;
}

GoToParameterController * CurveParameterController::goToParameterController() {
  return &m_goToParameterController;
}

}
