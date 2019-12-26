#include "generationwindowmainview.h"

GenerationWindowMainView::GenerationWindowMainView()
{

}

void GenerationWindowMainView::attachController(GenerationWindowMainController *controller)
{
    this->controller = controller;
}
