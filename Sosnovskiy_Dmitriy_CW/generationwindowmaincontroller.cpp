#include "generationwindowmaincontroller.h"

GenerationWindowMainController::GenerationWindowMainController()
{

}

void GenerationWindowMainController::attachView(GenerationWindowMainView* view)
{
    view->attachController(this);
    this->view = view;
}
