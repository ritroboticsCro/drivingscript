#include "killall.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;
KillAll::KillAll()
{

    system("gnome-terminal -x sh -c 'pgrep gnome-term >>kill.txt'");

    
    
    //system("gnome-terminal -x sh -c 'kill '"+i);

    //std::ifstream infile("tmp kill.txt");
    //std::string data(std::istreambuf_iterator<char>(infile), (std::istreambuf_iterator<char>()));

    //system("rm -f kill.txt");

    //cout << s;
}

