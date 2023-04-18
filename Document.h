// TA Adam E: I added the #ifndef and #define statements
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream>
#include <iostream>
#include <list>  //TA Adam E: This is the include statement for linked lists

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

using namespace std;
class Document {
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
    rapidjson::Document d;  // TA Adam E: I added the data-member Document d

   public:
    // TA Adam E: I added a default constructor for Document, because
    Document() = default;
    Document(string f) { FileName = f; };
    void changeFile(string);
    void parseDoc();
    string getText();
    string getTextBlurb();
    string getTitle();
    string getPublishDate();
    string getSite();
    string getURL();
    list<string> getPerson();
    list<string> getOrgs();
};

#endif
