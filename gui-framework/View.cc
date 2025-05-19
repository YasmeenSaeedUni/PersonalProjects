#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "View.h"

void View::menu(const vector<string>& menu, int& choice, const string& preamble)
{
  cout << endl;
  cout << "Please make a selection:"<< endl<<endl;
  cout << preamble << endl;
  for (int i = 0; i < menu.size(); ++i){
    cout<<"  ("<<i+1<<") "<<menu[i]<<endl;
  }
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > menu.size()) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::getNumber(int& num)
{
  cout << "Enter a number: ";
  cin >> num;
  while (num < 0) {
    cout << "Enter a number: ";
    cin >> num;
  }
}

