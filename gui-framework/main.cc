#include <iostream>
#include <random>
#include <sstream>
#include "Tester.h"
#include "TestControl.h"
#include <unistd.h>



using namespace std;

int main(){

    TestControl tcontrol;
    cout<<"Launching tests..."<<endl;
    tcontrol.launch();
    
    return 0;  
}


