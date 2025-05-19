#include "Tester.h"

// strangely difficult to get this to work correctly
void Tester::pressEnterToContinue(){
    std::cout << "Press enter to continue..."<<endl;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char c = cin.get();
    while ( c != '\n') { 
        c = cin.get();
    }
}

void Tester::clearInputBuffer(){
    char c = cin.get();
    while ( c != '\n') { 
        c = cin.get();
    }
}

void Tester::find(const vector<int>& keys, const string* search, int& error){
    int found = -1;
    error = 0;
    vector<int>::const_iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid]);
        if (found == string::npos){
            std::cout<<search[*ivid]<<" not found"<<endl;
            ++error;
        } 
    }
}

void Tester::find(const vector<int>& keys, const vector<string>& search, int& error){
    int found = -1;
    error = 0;
    vector<int>::const_iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid]);
        if (found == string::npos){
            std::cout<<search[*ivid]<<" not found"<<endl;
            ++error;
        } 
    }
}

void Tester::find(const vector<string>& toFind, int& error){
    int found = -1;
    error = 0;
    for (string tf: toFind){
        found = output.find(tf);
        if (found == string::npos){
            std::cout<<tf<<" not found"<<endl;
            ++error;
        } 
    }
}

void Tester::confirmAbsent(const vector<int>& keys, const string* search, int& error){
    int found = -1;
    error = 0;
    vector<int>::const_iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid]);
        if (found != string::npos){
            std::cout<<search[*ivid]<<" found but should not be"<<endl;
            ++error;
        } 
    }
}

void Tester::confirmAbsent(const vector<int>& keys, const vector<string>& search, int& error){
    int found = -1;
    error = 0;
    vector<int>::const_iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid]);
        if (found != string::npos){
            std::cout<<search[*ivid]<<" found but should not be"<<endl;
            ++error;
        } 
    }
}

void Tester::confirmAbsent(const vector<string>& absent, int& error){
    int found = -1;
    error = 0;
    for (string ab: absent){
        found = output.find(ab);
        if (found != string::npos){
            std::cout<<ab<<" found but should not be"<<endl;
            ++error;
        } 
    }
}

void Tester::findInOrder(const vector<int>& keys, const string* search, int& error){
    int found = -1;
    error = 0;
    vector<int>::const_iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid], found+1);
        if (found == string::npos){
            std::cout<<search[*ivid]<<" not found in order"<<endl;
            ++error;
        } 
    }
}

void Tester::findInOrder(const vector<int>& keys, const vector<string>& search, int& error){
    int found = -1;
    error = 0;
    vector<int>::const_iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid], found+1);
        if (found == string::npos){
            std::cout<<search[*ivid]<<" not found in order"<<endl;
            ++error;
        } 
    }
}

void Tester::findInOrder(const vector<string>& toFind, int& error){
    int found = -1;
    error = 0;
    for (string tf: toFind){
        found = output.find(tf, found+1);
        if (found == string::npos){
            std::cout<<tf<<" not found in order"<<endl;
            ++error;
        } 
    }
}

void Tester::initCapture(){
    oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream temp;
    strCout.swap(temp);
    std::cout.rdbuf( strCout.rdbuf() );
}

void Tester::endCapture(){
    std::cout.rdbuf( oldCoutStreamBuf );
    output = strCout.str();
    std::cout << output;
}

void Tester::ran(vector<int>& list, int count, int range){
    unordered_set<int> s;
    const int range_from  = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range-1);

    while (s.size() < count){
        s.insert(distr(generator));
    }
    unordered_set<int>::iterator it;
    for (it = s.begin(); it!=s.end();++it){
        list.push_back(*it);
    }
}

// generate and return a single random number in the range range_from to range_to - 1
int Tester::ran(int range_from, int range_to){
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to-1);
    return distr(generator);
}

