#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "IndexHandler.h"
#include "Document.h"
#include "Tree.h"
#include "QueryEngine.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include<sstream>
using namespace std;

class FileHandler {
    struct docWithMetrc{
        string docName;
        double metric;

        docWithMetrc(const string doc, const double met): docName(doc), metric(met){}
        bool operator< (const docWithMetrc& s) const {
            return metric > s.metric;
        }
    };

    IndexHandler i;
    QueryEngine q;
    set<string> intersect;
    set<docWithMetrc> top15;
    int numFiles;
    string mainWord;

public:
    // add file to update tree
    void updateIndex(const string&);
    // get results from tree
    void queryTreeWords(string, int count, const int&);
    void queryTreeNotWords(const string&);
    void queryHashPersons(const string&);
    void queryHashOrgs(const string&);
    unordered_set<string> temp;
    void queryPersons(const string &person);
    void queryOrgs(const string &orgs);

    // output resulting set
    void outputResults();
    void getTop50Words();

    void loadPersonIndex(){ i.loadPersistenceFileIndexPersons();};
    void loadOrgsIndex(){ i.loadPersistenceFileIndexOrgs();};
    void loadWordsIndex(){ i.loadPersistenceFileIndexWords();};

    void savePersonIndex(){ i.savePersistenceFileIndexPersons();};
    void saveOrgIndex(){ i.savePersistenceFileIndexOrgs();};
    void saveWordIndex(){ i.savePersistenceFileIndexWords();};

    void setNumFiles(const int a){numFiles = a;};
    void setMainWord(const string a){mainWord = a;};

    void top15Sets();
    void clear();
    
    void viewDoc(const int);
    void clearTop15(){ top15.clear();}
};
#endif
