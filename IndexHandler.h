#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "Tree.h"
#include "porter2_stemmer.h"
#include"IndexEntry.h"
#include <vector>
#include "HashTable.h"
#include<list>
#include <set>
#include<fstream>
#include<vector>
#include <algorithm>
#include<sstream>
#include<unordered_map>
class IndexHandler {
private:
    Tree<IndexEntry> TreeIndex;
    // HashTable<string, string> hashTablePersons;
    // HashTable<string, string> hashTableOrgs;
    int numWords=0;
    int treeSize=0;

public:
    // add words to tree
    void addDoc(const string&, const string&);

    // add persons
    void addPersons(const string&,list<string>);
    void addOrgs(const string&,list<string>);

    // get sets
    set<string>* getDocsFromTree(const string&);
    set<string>* getDocsFromHashPerson(const string&word);
    set<string>* getDocsFromHashOrgs(const string&word);

    int getNumWords(){return numWords;}
    int getTreeSize(){
        treeSize = TreeIndex.getSize();
        return treeSize;
    }
    // int getUniquePersons(){
    //     return hashTablePersons.getUniqueSize();
    // }
    // int getUniqueOrgs(){
    //     return hashTableOrgs.getUniqueSize();
    // }
    void getTop50Words();

    // load persistence files in
    void loadPersistenceFileIndexOrgs();
    void loadPersistenceFileIndexWords();
    void loadPersistenceFileIndexPersons();

    void savePersistenceFileIndexPersons();
    void savePersistenceFileIndexOrgs();
    void savePersistenceFileIndexWords();

    void clear();
};

#endif