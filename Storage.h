#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <sstream>
#include <string>
#include "WebPage.h"

using namespace std;

class Storage{
public:

    WebPage getPage(string url){

        ifstream file("pages.txt");

        string line;

        while(getline(file, line)){

            stringstream ss(line);

            string fileUrl;
            string title;
            string content;

            getline(ss, fileUrl, '|');
            getline(ss, title, '|');
            getline(ss, content, '|');

            if(fileUrl == url){
                return WebPage(fileUrl, title, content);
            }
        }

        return WebPage();
    }
};

#endif