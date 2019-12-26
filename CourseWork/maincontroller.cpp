#include "maincontroller.h"

MainController::MainController()
{

}

void MainController::attachView(MainView* attachableView)
{
    attachableView->attachController(this);
    this->view = attachableView;
}
