#include "IndexEntry.h"
#include<algorithm>
using namespace std;

IndexEntry::IndexEntry() {
    Word = "";
}

//addDocToldxEntry will take a string called docName as its argument and add it to the index entry
void IndexEntry::addDocToIdxEntry(const string& docName){
    // increase quantity
    auto it = uuidMap.find(docName);
    if(it != uuidMap.end()){
        it->second++;
        return;
    }
    // or add doc
    else{
        uuidMap[docName] = 1;
    }
}

//docNamesMapInsert takes a string called word and an integer called freq as its arguments and inserts them in to DocNames
void IndexEntry::docNamesMapInsert(const string &word, const int &freq) {
    uuidMap[word] = freq;
}
