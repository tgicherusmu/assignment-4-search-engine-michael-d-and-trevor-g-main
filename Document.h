// TA Adam E: I added the #ifndef and #define statements
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream>
#include <iostream>
#include <list>  //TA Adam E: This is the include statement for linked lists
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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
    string FileName;
    string text;
    string uuid;
    string title;
    string publishDate;
    string site;
    string url;
    vector<string> people;
    vector<string> orgs;
//    rapidjson::Document d;  // TA Adam E: I added the data-member Document d
    explicit Document(const string& filepath) { //todo: test this constructor
        FileName = filepath;
        ifstream f(filepath);
        rapidjson::IStreamWrapper wrap(f);
        rapidjson::Document d;
        d.ParseStream(wrap);

        uuid = d["uuid"].GetString();
        site = d["thread"]["site"].GetString();
        url = d["url"].GetString();
        title = d["title"].GetString();
        publishDate = d["published"].GetString();
        text = d["text"].GetString();

        for (auto& person : d["entities"]["persons"].GetArray()) {
            string name = person["name"].GetString();
            //todo: clean name, make sure it is all lowercase and replace spaces with '-'
            people.emplace_back(name);
        }

        for (auto& organ : d["entities"]["organizations"].GetArray()) {
            string name = organ["name"].GetString();
            //todo: clean name, make sure it is all lowercase and replace spaces with '-'
            orgs.emplace_back(name);
        }
    };
//    void changeFile(string);
    //^^^^^^delete this and create new document object instead

    //vector<string> getPersons() const;
    //vector<string> getOrgs() const;
    //vector<string> persons_vec;
    //vector<string> orgs_vec;
    //^^^^^^this can be deleted
//    string getText();
//    string getTextBlurb();
//    string getTitle();
//    string getPublishDate();
//    string getSite();
//    string getURL();
//    list<string> getPerson();
//    list<string> getOrgs();
    //^^^^all get functions can be deleted as well,ex. replace every getPerson with .person
//    int maxChars = 1000000;
};

#endif
