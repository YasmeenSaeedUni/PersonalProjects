
#include "TestControl.h"


    // int testPrintTextAreas();
    // int testPrintFlowPanels();
    // int testTextAreasinFlowPanel();

    // // Integration tests for CuWindow
    // int mwTestFlowPanels();
    // int mwTestTextAreas();

    // void testRenderWindow();

    // void studentTests();

vector<string> TestControl::menu ={
    
    "[2 marks] TextArea and Button test",
    "[3 marks] Panel test",
    "[4 marks] Component in FlowPanel test",
    "[4 marks] Component in AbsolutePanel test",
    "[4 marks] Panels in FlowPanel test",
    "[4 marks] Components in CuWindow test\n",
    
    "[21 marks] Run all automated tests and get mark\n\nRendering tests (see spec for expected output):\n",
    "[3 marks] Render test 1",
    "[3 marks] Render test 2\n\nMemory tests - use valgrind:\n",
    "[2 marks] Panel Memory tests",
    "[2 marks] CuWindow Memory tests\n\nStudent tests\n",
    "Student tests (optional)\n",
    
    
};


void TestControl::launch(){
    //get input, launch the appropriate test
    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice, "Automated tests:\n");
        switch(choice){
            
            case 1: testTextAreasAndButtons(); break;
            case 2: testPanels(); break;
            case 3: testComponentsInFlowPanel(); break;
            case 4: testComponentsInAbsolutePanel(); break;
            case 5: testPanelsInFlowPanel(); break;
            case 6: testPanelsinWindow(); break;

            case 7: cout<<"Total score: "<<
                    testTextAreasAndButtons() 
                    + testPanels() 
                    + testComponentsInFlowPanel() 
                    + testComponentsInAbsolutePanel()
                    + testPanelsInFlowPanel()
                    + testPanelsinWindow()<<"/21"<<endl; break;
            case 8: testPanelsinWindowRenderTest(); break;
            case 9: testRenderWindow(); break;
            case 10: testPanelMemory(); break;
            case 11: testWindowMemory(); break;
            case 12: studentTests(); break;
        }
    }
}

void TestControl::studentTests(){
    cout<<"Student tests"<<endl;
    cout<<"No tests found"<<endl;
    // Make a window, try stuff out
    RGB colour(0, 255, 0);  // change this to your favourite colour
    CuWindow window("Test", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 450, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->add(textArea1);
    panel2->add(textArea2);
    panel3->add(textArea3);
    panel4->add(textArea4);
    panel5->add(textArea5);
    panel6->add(textArea6);

    window.add(panel1);
    window.add(panel2);
    window.add(panel3);
    window.add(panel4);
    window.add(panel5);
    window.add(panel6);

    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();

    // make and add panels, add components to panels, etc
    // You should test, at least, different TextArea colours, different Window colours, 
    // and different placements of FlowPanels and TextAreas. There should be at least 
    // 4 different configurations of FlowPanels and TextAreas in your test. Each configuration must have
    // at least 2 FlowPanels and 2 TextAreas.

    // You can use tester.pressEnterToContinue() to pause the program between configurations
}



int TestControl::testTextAreasAndButtons(){
    string labels[5] = {"TextArea 1", "Button 2", "TextArea 3", "Button 4", "TextArea 5"};
    string ids[5] = {"ta1", "b2", "ta3", "b4", "ta5"};
    Component* components[5];
    string ycoords[5] = {"10", "70", "130", "190", "250"};
    string widths[5] = {"20", "31", "42", "53", "64"};
    for (int i = 0; i < 5; i++){
        if (i % 2 == 0){
            components[i] = new TextArea(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[i], labels[i]);
        } else {
            components[i] = new Button(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[i], labels[i], RGB::BLACK(), RGB::WHITE());
        }
    }

    cout<<"Component print test"<<endl<<endl;

    tester.initCapture();
    for (int i = 0; i < 5; i++){
        cout<<endl;
        components[i]->print();
    }
    tester.endCapture();
    cout<<endl;

    int score = 0;
    int error = 0;
    tester.findInOrder({0,1,2,3,4}, labels, error);

    if (error == 0){
        cout<<"Label printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Label printing test failed"<<endl;
    }


    error = 0;

    tester.findInOrder({0,1,2,3,4}, widths, error);

    if (error == 0){
        cout<<"Width printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Width printing test failed"<<endl;
    }

    cout<<"Component print test score: "<<score<<"/2"<<endl<<endl;

    cout<<"Deleting components"<<endl;

    for (int i = 0; i < 5; i++){
        delete components[i];
    }

    return score;
}

int TestControl::testPanels(){
    string ids[5] = {"FlowPanel 1", "AbsolutePanel 2", "FlowPanel 3", "AbsolutePanel 4", "FlowPanel 5"};
    Panel* panels[5];
    string ycoords[5] = {"10", "70", "130", "190", "250"};
    string widths[5] = {"20", "31", "42", "53", "64"};
    for (int i = 0; i < 5; i++){
        if (i % 2 == 0){
            panels[i] = new FlowPanel(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[i]);
        } else {
            panels[i] = new AbsolutePanel(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[i]);
        }
    }

    cout<<"Panel print test"<<endl<<endl;

    tester.initCapture();
    for (int i = 0; i < 5; i++){
        cout<<endl;
        panels[i]->print();
    }
    tester.endCapture();
    cout<<endl;

    int score = 0;
    int error = 0;
    tester.findInOrder({0,1,2,3,4}, ids, error);

    if (error == 0){
        cout<<"ID printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"ID printing test failed"<<endl;
    }

    error = 0;
    tester.findInOrder({0,1,2,3,4}, ycoords, error);

    if (error == 0){
        cout<<"Y coordinate printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Y coordinate printing test failed"<<endl;
    }

    error = 0;

    tester.findInOrder({0,1,2,3,4}, widths, error);

    if (error == 0){
        cout<<"Width printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Width printing test failed"<<endl;
    }

    cout<<"Panel print test score: "<<score<<"/3"<<endl<<endl;

    cout<<"Deleting Panels"<<endl;

    for (int i = 0; i < 5; i++){
        delete panels[i];
    }

    return score;
}

int TestControl::testComponentsInFlowPanel(){
    FlowPanel panel(10, 10, 200, 200, "FlowPanel 1");
    vector<string> ids = {"ta1", "b2", "ta3", "b4", "ta5","b6"};
    vector<string> text = {"TextArea 1", "Button 2", "TextArea 3", "Button 4", "TextArea 5", "Button 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    Component* components[6];

    for (int i = 0; i < 6; i++){
        if (i % 2 == 0){
            components[i] = new TextArea(rects[i], ids[i], text[i]);
        } else {
            components[i] = new Button(rects[i], ids[i], text[i], RGB::BLACK(), RGB::WHITE());
        }
        panel.add(components[i]);
    }


    cout<<"FlowPanel components test"<<endl<<endl;

    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    float score = 0;
    int error = 0;
    tester.findInOrder(text, error);

    if (error == 0){
        cout<<"Correct text found in order, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Not all text found, or not in order, test failed"<<endl;
    }

    cout<<"Removing textArea 3"<<endl<<endl;
    Component* removed = panel.remove("ta3");

    error = 0;
    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    error = 0;

    tester.findInOrder({0,1,3,4,5}, text, error);

    if (error == 0){
        cout<<"Correct components found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Not all TextAreas found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"TextArea 3"}, error);

    if (error == 0){
        cout<<"TextArea 3 not found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"TextArea 3 was not removed, test failed"<<endl;
    }

    if (removed != components[2]){
        cout<<"Incorrect TextArea returned (or maybe nullptr), test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    cout<<"Removing components 1 and 6 by *index*"<<endl<<endl;

    if (panel.remove(0)!=components[0]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    if (panel.remove(3)!=components[5]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    error = 0;
    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"Button 2", "Button 4"}, error);

    if (error == 0){
        cout<<"Button 2 and 4 found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Button 2 or 4 was removed/not found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"TextArea 1", "Button 6"}, error);

    if (error == 0){
        cout<<"Components 1 and 6 not found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Components 1 or 6 was not removed, test failed"<<endl;
    }

    cout<<"FlowPanel components test score: "<<score<<"/4"<<endl<<endl;

    cout<<endl<<"Deleting removed components"<<endl;

    delete components[2];
    delete components[0];
    delete components[5];

    return score;
}

int TestControl::testComponentsInAbsolutePanel(){
    AbsolutePanel panel(10, 10, 200, 200, "AbsolutePanel 1");
    vector<string> ids = {"ta1", "b2", "ta3", "b4", "ta5","b6"};
    vector<string> text = {"TextArea 1", "Button 2", "TextArea 3", "Button 4", "TextArea 5", "Button 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    Component* components[6];

    for (int i = 0; i < 6; i++){
        if (i % 2 == 0){
            components[i] = new TextArea(rects[i], ids[i], text[i]);
        } else {
            components[i] = new Button(rects[i], ids[i], text[i], RGB::BLACK(), RGB::WHITE());
        }
        panel.add(components[i]);
    }


    cout<<"AbsolutePanel components test"<<endl<<endl;

    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    float score = 0;
    int error = 0;
    tester.findInOrder(text, error);

    if (error == 0){
        cout<<"Correct text found in order, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Not all text found, or not in order, test failed"<<endl;
    }

    cout<<"Removing textArea 3"<<endl<<endl;
    Component* removed = panel.remove("ta3");

    error = 0;
    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    error = 0;

    tester.findInOrder({0,1,3,4,5}, text, error);

    if (error == 0){
        cout<<"Correct components found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Not all TextAreas found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"TextArea 3"}, error);

    if (error == 0){
        cout<<"TextArea 3 not found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"TextArea 3 was not removed, test failed"<<endl;
    }

    if (removed != components[2]){
        cout<<"Incorrect TextArea returned (or maybe nullptr), test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    cout<<"Removing components 1 and 6 by *index*"<<endl<<endl;

    if (panel.remove(0)!=components[0]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    if (panel.remove(3)!=components[5]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    error = 0;
    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"Button 2", "Button 4"}, error);

    if (error == 0){
        cout<<"Button 2 and 4 found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Button 2 or 4 was removed/not found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"TextArea 1", "Button 6"}, error);

    if (error == 0){
        cout<<"Components 1 and 6 not found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Components 1 or 6 was not removed, test failed"<<endl;
    }

    cout<<"FlowPanel components test score: "<<score<<"/4"<<endl<<endl;

    cout<<endl<<"Deleting removed components"<<endl;

    delete components[2];
    delete components[0];
    delete components[5];

    return score;
}

int TestControl::testPanelsInFlowPanel(){
    FlowPanel panel(10, 10, 200, 200, "Main FlowPanel");
    vector<string> ids = {"FlowPanel 1", "AbsolutePanel 2", "FlowPanel 3", "AbsolutePanel 4", "FlowPanel 5", "AbsolutePanel 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    Component* components[6];

    for (int i = 0; i < 6; i++){
        if (i % 2 == 0){
            components[i] = new FlowPanel(rects[i], ids[i]);
        } else {
            components[i] = new AbsolutePanel(rects[i], ids[i]);
        }
        panel.add(components[i]);
    }


    cout<<"FlowPanel components test"<<endl<<endl;

    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    float score = 0;
    int error = 0;
    tester.findInOrder(ids, error);

    if (error == 0){
        cout<<"Correct ids found in order, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Not all ids found, or not in order, test failed"<<endl;
    }

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    Component* removed = panel.remove("FlowPanel 3");

    error = 0;
    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    error = 0;

    tester.findInOrder({0,1,3,4,5}, ids, error);

    if (error == 0){
        cout<<"Correct components found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Not all TextAreas found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"FlowPanel 3"}, error);

    if (error == 0){
        cout<<"FlowPanel 3 not found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"FlowPanel 3 was not removed, test failed"<<endl;
    }

    if (removed != components[2]){
        cout<<"Incorrect FlowPanel returned (or maybe nullptr), test failed"<<endl;
    } else {
        cout<<"Correct FlowPanel returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    cout<<"Removing panels 1 and 6 by *index*"<<endl<<endl;

    if (panel.remove(0)!=components[0]){
        cout<<"Incorrect Panel removed, test failed"<<endl;
    } else {
        cout<<"Correct Panel returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    if (panel.remove(3)!=components[5]){
        cout<<"Incorrect Panel removed, test failed"<<endl;
    } else {
        cout<<"Correct Panel returned, test passed, 0.5 marks"<<endl;
        score += 0.5;
    }

    error = 0;
    tester.initCapture();
    panel.printComponents();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"AbsolutePanel 2", "AbsolutePanel 4"}, error);

    if (error == 0){
        cout<<"AbsolutePanel 2 and 4 found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"AbsolutePanel 2 or 4 was removed/not found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"FlowPanel 1", "AbsolutePanel 6"}, error);

    if (error == 0){
        cout<<"Panels 1 and 6 not found after removal, test passed, 0.5 marks"<<endl;
        score += 0.5;
    } else {
        cout<<"Panels 1 or 6 was not removed, test failed"<<endl;
    }

    cout<<"Panels in panels test score: "<<score<<"/4"<<endl<<endl;

    cout<<endl<<"Deleting removed components"<<endl;

    delete components[2];
    delete components[0];
    delete components[5];

    return score;
}



int TestControl::testPanelsinWindow(){
    RGB colour(0, 255, 0);
    CuWindow window("Test 10", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 450, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->add(textArea1);
    panel2->add(textArea2);
    panel3->add(textArea3);
    panel4->add(textArea4);
    panel5->add(textArea5);
    panel6->add(textArea6);

    window.add(panel1);
    window.add(panel2);
    window.add(panel3);
    window.add(panel4);
    window.add(panel5);
    window.add(panel6);

    cout<<"CuWindow panels test 10"<<endl<<endl;
   
    // window.draw();
    // tester.pressEnterToContinue();
    // tester.pressEnterToContinue();
    tester.initCapture();
    window.printComponents();
    tester.endCapture();

    int score = 0;
    int error = 0;
    vector<string> panelNames = {"FlowPanel 1", "FlowPanel 2", "FlowPanel 3", "FlowPanel 4", "FlowPanel 5", "FlowPanel 6"};
    tester.find(panelNames, error);

    if (error == 0){
        cout<<"Correct panels found, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all FlowPanels found, test failed"<<endl;
    }

    error = 0;

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    if (panel3!= window.remove("FlowPanel 3")){
        cout<<"Incorrect FlowPanel removed, test failed"<<endl;
    } else {
        cout<<"Correct FlowPanel removed, test passed, 1 mark"<<endl;
        score += 1;
    }


    error = 0;
    tester.initCapture();
    window.printComponents();
    tester.endCapture();

    error = 0;

    tester.find({0,1,3,4,5}, panelNames, error);

    if (error == 0){
        cout<<"Correct panels found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all FlowPanels found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"FlowPanel 3"}, error);

    if (error == 0){
        cout<<"FlowPanel 3 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanel 3 was not removed, test failed"<<endl;
    }

    // window.draw();
    // tester.pressEnterToContinue();

    cout<<"CuWindow panels test score: "<<score<<"/4"<<endl<<endl;

    return score;
}

int TestControl::testPanelsinWindowRenderTest(){
    RGB colour(0, 255, 0);
    CuWindow window("Test 10", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 450, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->add(textArea1);
    panel2->add(textArea2);
    panel3->add(textArea3);
    panel4->add(textArea4);
    panel5->add(textArea5);
    panel6->add(textArea6);

    window.add(panel1);
    window.add(panel2);
    window.add(panel3);
    window.add(panel4);
    window.add(panel5);
    window.add(panel6);

    cout<<"[2 marks] Check for correct panels (see spec diagram)"<<endl<<endl;
   
    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
    
    cout<<"Removing FlowPanel 3"<<endl<<endl;
    if (panel3!= window.remove("FlowPanel 3")){
        cout<<"Incorrect FlowPanel removed"<<endl;
    } else {
        cout<<"Correct FlowPanel removed"<<endl;
    }

    cout<<"[2 marks] Check for correct panels after removal (see spec diagram)"<<endl<<endl;

    window.draw();
    tester.pressEnterToContinue();

    return 0;
}

int TestControl::testPanelMemory(){
    AbsolutePanel panel(10, 10, 200, 200, "AbsolutePanel Main");
    vector<string> ids = {"comp1", "comp2", "comp3", "comp4", "comp5","comp6"};
    vector<string> text = {"TextArea 1", "Button 2", "FlowPanel 3", "AbsolutePanel 4", "Button 5", "TextArea 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    Component* components[6];

    cout<<"Adding 6 components to AbsolutePanel"<<endl<<endl;

    components[0] = new TextArea(rects[0], ids[0], text[0]);
    components[1] = new Button(rects[1], ids[1], text[1], RGB::BLACK(), RGB::WHITE());
    components[2] = new FlowPanel(rects[2], ids[2]);
    components[3] = new AbsolutePanel(rects[3], ids[3]);
    components[4] = new Button(rects[4], ids[4], text[4], RGB::BLACK(), RGB::WHITE());
    components[5] = new TextArea(rects[5], ids[5], text[5]);

    for (int i = 0; i < 6; i++){
        panel.add(components[i]);
    }


    cout<<"Removing FlowPanel 3"<<endl<<endl;
    panel.remove("comp3");

    cout<<"Removing components 1 and 6 by *index*"<<endl<<endl;

    panel.remove(0);

    panel.remove(3);



    cout<<endl<<"Deleting removed components, test with valgrind and watch for memory errors on exit"<<endl;

    tester.pressEnterToContinue();
    tester.pressEnterToContinue();

    delete components[2];
    delete components[0];
    delete components[5];

    return 0;
 
}


int TestControl::testWindowMemory(){
    RGB colour(0, 255, 0);
    CuWindow window("Test 11", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 550, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->add(textArea1);
    panel2->add(textArea2);
    panel3->add(textArea3);
    panel4->add(textArea4);
    panel5->add(textArea5);
    panel6->add(textArea6);

    window.add(panel1);
    window.add(panel2);
    window.add(panel3);
    window.add(panel4);
    window.add(panel5);
    window.add(panel6);

    cout<<"CuWindow panels test"<<endl<<endl;
   
    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
    

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    window.remove("FlowPanel 3");

    cout<<"Removing FlowPanel 6"<<endl<<endl;
    window.remove("FlowPanel 6");


    window.draw();
    tester.pressEnterToContinue();

    cout<<"Deleting removed FlowPanels, test with valgrind and watch for memory errors on exit"<<endl;

    delete panel3;
    // delete panel2;
    delete panel6;


    return 0;
}



void TestControl::testRenderWindow(){

    RGB colour(0, 255, 0);

    CuWindow window("Test", 600, 600, colour);
    FlowPanel *panel1 = new FlowPanel(0, 0, 600, 300, "FlowPanel 1");
    FlowPanel *panel2 = new FlowPanel(0, 300, 600, 300, "FlowPanel 2");
    FlowPanel *panel3 = new FlowPanel(0, 0, 100, 60, "FlowPanel 3");

    TextArea* textArea1 = new TextArea({10, 10, 80, 50}, "ta1","TextArea*1hereisalongstring");
    TextArea* textArea2 = new TextArea({10, 70, 280, 150}, "ta2","TextArea* 2");
    Button* button3 = new Button({10, 130, 280, 70}, "ta3", "Button 3");
    TextArea* textArea4 = new TextArea({80, 210, 180, 90}, "ta4","TextArea* 4 here is a long string, in fact this is a very long string, let's see what happens");
    TextArea* textArea5 = new TextArea({80, 210, 180, 90}, "ta5","TextArea* 5 here is a long string, in fact this is a very long string, let's see what happens");

    Button* button1 = new Button({5,5,80,40},"b1", "Button 1");
    panel1->add(textArea1);
    panel1->add(textArea2);
    panel1->add(button3);
    panel1->add(textArea4);

    panel2->add(new TextArea(*textArea1 ));
    panel2->add(new TextArea(*textArea2 ));
    panel2->add(textArea5);
   
    panel3->add(button1);
    panel2->add(panel3);

    window.add(panel1);
    window.add(panel2);

    // register textareas and buttons for click events
    // window.registerComponent(textArea1);
    // window.registerComponent(textArea2);
    // window.registerComponent(button3);
    // window.registerComponent(textArea4);
    // window.registerComponent(textArea5);
    // window.registerComponent(b1);

    cout<<"CuWindow render test"<<endl<<endl;

    
    window.draw();
    
    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    tester.pressEnterToContinue(); // sigh, input buffers

    cout<<"Changing textArea 2, making Button 3 too high to fit"<<endl;
    textArea2->setText("This is a new string for textArea 2. Let's make it extra long so we can see the wrapping feature");
    button3->setHeight(400);
    //added in to match figure 2 in asisgnment specs since there was no remove function
    cout<<"Removing textArea 4."<<endl;
    delete panel1->remove("ta4");
    window.draw();

    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    
}

