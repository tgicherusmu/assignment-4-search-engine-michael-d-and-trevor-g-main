#include <fstream>
#include <iostream>
#include "Document.h"
#include <sstream>
#include <algorithm>

using namespace std;

//changeFile need to take in a string as an argument and set FileName variable to that string
void Document::changeFile(string c){ 
    FileName = c;
    parseDoc();
}
//parseDoc needs to read in a file using ifsreamm and wraps it using StreamWrapper
void Document::parseDoc(){
    // read in file
    ifstream f(FileName);

    // wrap istream
    rapidjson::IStreamWrapper wrap(f);
 
    // get all the text from file
    char text[1000000];
    d.ParseStream(wrap);

}
string Document::getText(){ //getText returns the text from the JSON file //getText returns the text from the JSON file
    return d["text"].GetString();
}
//getTextBlurb needs to return a string that contains the first 32 words of text from the JSON file
string Document::getTextBlurb(){
    string temp = d["text"].GetString();
    string temp2, blurb;

    stringstream ss(temp);

    getline(ss,temp2,' ');
    blurb+=temp2;

    int i=0;
    while(getline(ss,temp2,' ')){
        // get 30 words
        temp2.erase(std::remove(temp2.begin(), temp2.end(), '\n'), temp2.end());
        if(i>32)
            break;
        if(i==16){
            blurb+="\n"+temp2;
            ++i;
            continue;

        }
        blurb+=" "+temp2;
        ++i;
    }
    return blurb+"...";
}

//getTitle needs to return the title of teh file
string Document::getTitle(){ 
    return d["title"].GetString();
}
//getPublishDate needs to return the published date of JSON
string Document::getPublishDate(){
    return d["published"].GetString();
}
//getSite needs to return the URL of the file
string Document::getSite(){
    return d["url"].GetString();
}
//getPerson needs to return a list of people mentioned in the file
list<string> Document::getPerson(){
    list<string> persons;
    for (rapidjson::Value::ConstValueIterator itr = d["entities"].GetObject()["persons"].Begin(); itr != d["entities"].GetObject()["persons"].End(); ++itr){
        persons.emplace_back(itr->GetObject()["name"].GetString());
    }

   return persons;
}
//getOrgs needs to return a list of organizations mentioned in the file
list<string> Document::getOrgs(){
    list<string> orgs;
    for (rapidjson::Value::ConstValueIterator itr = d["entities"].GetObject()["organizations"].Begin(); itr != d["entities"].GetObject()["organizations"].End(); ++itr){
        orgs.emplace_back(itr->GetObject()["name"].GetString());
    }

    return orgs;
}