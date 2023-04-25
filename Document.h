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
    //CODE REVIEW COMMENTS:
    //return all functions by reference
    //make all variables public
    //vector of people, vector of orgs instead of string
    //Delete rapidjson document, instead when making document object pass json document by reference and automatically fill all the strings  in .h file (doing this in constructor)
   public:
    // TA Adam E: I added a default constructor for Document, because
    Document() = default;
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
    Document(string f) { FileName = f; };
    void changeFile(string);
    //^^^^^^delete this and create new document object instead
    void parseDoc();
    //^^^^^^this can be deleted
    string getText();
    string getTextBlurb();
    string getTitle();
    string getPublishDate();
    string getSite();
    string getURL();
    list<string> getPerson();
    list<string> getOrgs();
    //^^^^all get functions can be deleted as well,ex. replace every getPerson with .person
    int maxChars = 1000000;
};

#endif
