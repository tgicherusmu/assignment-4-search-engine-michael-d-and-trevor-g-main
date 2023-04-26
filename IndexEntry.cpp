//addDocToldxEntry will take a string called docName as its argument and add it to the index entry
//second method called operator== takes an IndexEntry called s as its argument returns true if indexentry's word field is less than s's word field
//operator< takes an IndexEntry called s as its argument and returns  true true if this InexEntry's Word field is less than s's word field
//operator> takes an IndexEntry called s as its argument and returns true if this IndexEntry's word field is greater than s's word field
//docNameSeInsert takes a string called word as an argument and puts it in DocNamesSet
//docNamesMapInsert takes a string called word and an integer called freq as its arguments and inserts them in to DocNames

#include "IndexEntry.h"
#include<algorithm>
using namespace std;


IndexEntry::IndexEntry() {
    Word = "";
}

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

// bool IndexEntry::operator== (const IndexEntry& s) const {
//     return Word == s.Word;
// }
// bool IndexEntry::operator< (const IndexEntry& s) const {
//     return Word < s.Word;
// }
// bool IndexEntry::operator> (const IndexEntry& s) const {
//     return s.Word < Word;
// }
//
//void IndexEntry::docNameSetInsert(const string &word) {
//    DocNamesSet.insert(word);
//}

void IndexEntry::docNamesMapInsert(const string &word, const int &freq) {
    uuidMap[word] = freq;
}
