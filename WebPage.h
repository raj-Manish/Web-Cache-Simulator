#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <string>
using namespace std;

class WebPage{
public:

    string url;
    string title;
    string content;

    WebPage(){}

    WebPage(string u, string t, string c){
        url = u;
        title = t;
        content = c;
    }
};

#endif