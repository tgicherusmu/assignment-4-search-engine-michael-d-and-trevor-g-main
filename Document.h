//#include "Document.h"
#include <fstream>
#include <iostream>

using namespace std;
class Document{
    private:
        string FileName;
        string text;
        string textBlurb;
        string title;
        string publishDate;
        string site;
        string url;
        string person;
        string orgs;
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