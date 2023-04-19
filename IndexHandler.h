#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "Tree.h"
#include "porter2_stemmer.h"
#include"IndexEntry.h"
#include <vector>
#include<list>
#include <set>
#include<fstream>
#include<vector>
#include <algorithm>
#include<sstream>
#include<unordered_map>
class IndexHandler {
private:
    AvlTree<IndexEntry> TreeIndex;
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
    //set<string>* getDocsFromHashPerson(const string&word);
    //set<string>* getDocsFromHashOrgs(const string&word);
    int size;
    int getSize(){ return size;}
    int getNumWords(){return numWords;}
    int getSet(const string&word, set<string>&set);
    int getEntry(const string&word, IndexEntry&entry);
    int getTreeSize(){
        treeSize = TreeIndex.getSize();
        return treeSize;
    }
    int getUniquePersons(){
        return hashTablePersons.getUniqueSize();
    }
    int getUniqueOrgs(){
        return hashTableOrgs.getUniqueSize();
    }
    void getTop50Words();

    void clearElements();
    void clear();
    void emptyTree();

//   void nameOfDocSetInsert(fileName); 
  // void nameOfDocsMapInsert(fileName, freq); 

    // load persistence files in
    void loadPersistenceFileIndexOrgs();
    void loadPersistenceFileIndexWords();
    void loadPersistenceFileIndexPersons();

    void savePersistenceFileIndexPersons();
    void savePersistenceFileIndexOrgs();
    void savePersistenceFileIndexWords();


};

#endif
