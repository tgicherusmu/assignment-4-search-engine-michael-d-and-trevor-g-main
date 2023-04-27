#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream> //file input/output
#include <iostream> 
#include <list>  //linked lists
#include <algorithm> //for std::transform
#include <sstream> //for std::stringstream
#include <vector> //for vectors

#include "rapidjson/document.h" //for parsing json files
#include "rapidjson/istreamwrapper.h" //for parsing json files

using namespace std;
class Document {
  public:
    string FileName;
    string text; 
    string uuid;
    string title;
    string publishDate;
    string site;
    string url;
    vector<string> people;
    vector<string> orgs; 
    //Delete rapidjson document, instead when making document object pass json document by reference and automatically fill all the strings  in .h file (doing this in constructor)
    //rapidjson::Document d;

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
};

#endif