#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>
#include <vector>

#include "CuWindow.h"
#include "View.h"
#include "Tester.h"
#include "FlowPanel.h"
#include "TextArea.h"
#include "Button.h"
#include "AbsolutePanel.h"
#include "Panel.h"


using namespace std;


class TestControl
{
  public:
    
    void launch();
    

  private:
    int testTextAreasAndButtons();
    int testPanels();
    int testComponentsInFlowPanel();
    int testComponentsInAbsolutePanel();
    int testPanelsInFlowPanel();

    // Integration tests for CuWindow
    int testPanelsinWindow();

    // deprecated
    // int mwTestTextAreas();

    int testPanelMemory();
    int testWindowMemory();

    void testRenderWindow();
    int testPanelsinWindowRenderTest();

    void studentTests();
  

    View view;
    Tester tester;

    static vector<string> menu;



    
};

#endif
