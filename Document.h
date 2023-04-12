//#include "Document.h"
#include <fstream>
#include <iostream>

using namespace std;
class Document{
    public:
        Document(string);
        void changeFile(string);
        void parseDoc();
        string getText();
        string getTextBlurb();
        string getTitle();
        string getPublishDate();
        string getSite();
        string getURL();
        string getPerson();
        string getOrgs();
        
};