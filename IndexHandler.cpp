#include "IndexHandler.h"
#include "FilterEntry.h"
#include "Tree.h"
#include <utility>
#include<vector>
#include <iostream>
#include<unordered_map>
#include <set>
#include <algorithm>
#include "IndexEntry.h"
// list of stop words
//CODE REVIEW COMMENTS:
//remove non alpha characters
//watch out for apostrophies
// add both versions for every word for an apostrophies if we dont clear
//change all sets to unordered
// insert stopword vector
set<string> theStopWords{
    "able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after", "afterwards",
    "again", "against", "ago", "ahead", "ain't", "all", "allow", "allows", "almost", "alone", "along", "alongside",
    "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst", "an", "and", "another", "any",
    "anybody", "anyhow", "anyone", "anything", "anyway", "anyways", "anywhere", "apart", "appear", "appreciate",
    "appropriate", "are", "aren't", "around", "as", "a's", "aside", "ask", "asking", "associated", "at", "available", "away",
    "awfully", "back", "backward", "backwards", "be", "became", "because", "become", "becomes", "becoming", "been", "before",
    "beforehand", "begin", "behind", "being", "believe", "below", "beside", "besides", "best", "better", "between", "beyond",
    "both", "brief", "but", "by", "came", "can", "cannot", "cant", "can't", "caption", "cause", "causes", "certain",
    "certainly", "changes", "clearly", "c'mon", "co", "co.", "com", "come", "comes", "concerning", "consequently", "consider",
    "considering", "contain", "containing", "contains", "corresponding", "could", "couldn't", "course", "c's", "currently",
    "dare", "daren't", "definitely", "described", "despite", "did", "didn't", "different", "directly", "do", "does", "doesn't",
    "doing", "done", "don't", "down", "downwards", "during", "each", "edu", "eg", "eight", "eighty", "either", "else",
    "elsewhere", "end", "ending", "enough", "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every",
    "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example", "except", "fairly", "far", "farther",
    "few", "fewer", "fifth", "first", "five", "followed", "following", "follows", "for", "forever", "former", "formerly",
    "forth", "forward", "found", "four", "from", "further", "furthermore", "get", "gets", "getting", "given", "gives", "go",
    "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't", "half", "happens", "hardly", "has", "hasn't", "have",
    "haven't", "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein", "here's",
    "hereupon", "hers", "herself", "he's", "hi", "him", "himself", "his", "hither", "hopefully", "how", "howbeit", "however",
    "hundred", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.", "indeed", "indicate",
    "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll",
    "its", "it's", "itself", "i've", "just", "k", "keep", "keeps", "kept", "know", "known", "knows", "last", "lately", "later",
    "latter", "latterly", "least", "less", "lest", "let", "let's", "like", "liked", "likely", "likewise", "little", "look",
    "looking", "looks", "low", "lower", "ltd", "made", "mainly", "make", "makes", "many", "may", "maybe", "mayn't", "me", "mean",
    "meantime", "meanwhile", "merely", "might", "mightn't", "mine", "minus", "miss", "more", "moreover", "most", "mostly", "mr",
    "mrs", "much", "must", "mustn't", "my", "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need", "needn't",
    "needs", "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non",
    "none", "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing", "notwithstanding", "novel", "now", "nowhere",
    "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones", "one's", "only", "onto", "opposite",
    "or", "other", "others", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over", "overall",
    "own", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus", "possible", "presumably", "probably",
    "provided", "provides", "que", "quite", "qv", "rather", "rd", "re", "really", "reasonably", "recent", "recently", "regarding",
    "regardless", "regards", "relatively", "respectively", "right", "round", "said", "same", "saw", "say", "saying", "says",
    "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "sent",
    "serious", "seriously", "seven", "several", "shall", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't",
    "since", "six", "so", "some", "somebody", "someday", "somehow", "someone", "something", "sometime", "sometimes", "somewhat",
    "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure", "take", "taken",
    "taking", "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that'll", "thats", "that's", "that've", "the",
    "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "there'd", "therefore", "therein",
    "there'll", "there're", "theres", "there's", "thereupon", "there've", "these", "they", "they'd", "they'll", "they're",
    "they've", "thing", "things", "think", "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three",
    "through", "throughout", "thru", "thus", "till", "to", "together", "too", "took", "toward", "towards", "tried", "tries",
    "truly", "try", "trying", "t's", "twice", "two", "un", "under", "underneath", "undoing", "unfortunately", "unless", "unlike",
    "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value",
    "various", "versus", "very", "via", "viz", "vs", "want", "wants", "was", "wasn't", "way", "we", "we'd", "welcome", "well",
    "we'll", "went", "were", "we're", "weren't", "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence",
    "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon", "wherever", "whether", "which",
    "whichever", "while", "whilst", "whither", "who", "who'd", "whoever", "whole", "who'll", "whom", "whomever", "who's", "whose",
    "why", "will", "willing", "wish", "with", "within", "without", "wonder", "won't", "would", "wouldn't", "yes", "yet", "you",
    "you'd", "you'll", "your", "you're", "yours", "yourself", "yourselves", "you've", "zero"};
//make stopword list a unordered set

// add an unordered map called hashed word that maps strings to strings
unordered_map<string, string> theHashedWords;
//Trevor Note: addPersons and addOrgs need to be added back
// //make a function called addPerson that takes in nameOfDoc and a list of strings called persons. it should iterate through each string in the list and insert it into a hashtable called hashTablePersons along with document anmes
 //void IndexHandler::addPersons(const string&nameOfDoc, list<string> persons){
   //  for (auto it=persons.begin(); it != persons.end(); ++it)
     //    hashTablePersons.insert(*it, nameOfDoc);
 //}
// //addOrds function will take two arguments, a string called nameOfDoc and a list of strings called persons. It iterates through each string in the list and inserts it into a hash table called hashTableOrds along with the document name
 //void IndexHandler::addOrgs(const string&nameOfDoc, list<string> persons){
   //  for (auto it=persons.begin(); it != persons.end(); ++it)
     //    hashTableOrgs.insert(*it, nameOfDoc);
 //}

//void IndexHandler::addPersons(const string&nameOfDoc, list<string> persons){
  //  for (auto it=persons.begin(); it != persons.end(); ++it)
    //    personsList.push_back(make_pair(*it, nameOfDoc));
//}
//void IndexHandler::addOrgs(const string&nameOfDoc, list<string> persons){
  //  for (auto it=persons.begin(); it != persons.end(); ++it)
    //    orgsList.push_back(make_pair(*it, nameOfDoc));
//}

// the function addDoc takes two arguments a string called nameOfDoc and a string called persons. it iterates through seach string and inserts it into the hashtable hashTableOrgs along with the ducment names
// a dunction addDoc will take two arguemnsta a tring called nameOfDoc and a string called DocText. It extracts all the words from the text using stringstream then checks to see if the word is a stop word
void IndexHandler::addDoc(const Document& doc) {
    // put text of file in ss
    stringstream ss(doc.text);
    unordered_map<string, int> wordMap; //maps word to appearance count for this document

    // extract the words
    string word;
    while (ss >> word) {
        //todo:
            //make everything in word lower case to clean
            //remove all non alpha character or just remove commas and periods from the end and beginning of words
        auto it = theStopWords.find(word);  // check if word is in stoplist
        if (it != theStopWords.end()) {     // if it is in the stoplist, continue
            continue;
        }

        // TA Adam E:  you only want to increment the number of words every time you find a new word? right now, you incremenet for every word you have
//        numWords++;  // increment number of words
        // check if word has been hashed
//        auto it2 = theHashedWords.find(word);  // check if word is in theHashedWords
//        if (it2 != theHashedWords.end()) {     // if it is in theHashedWords, continue
//            word = theHashedWords[word];       // set word to the hashed version of the word
//
//        } else {  //
//            // get stemmed version of word
//            string temp = word;
//            //Porter2Stemmer::trim(word);
//            Porter2Stemmer::stem(word);
//            // add to table
//            theHashedWords[temp] = word;
//            theHashedWords[word] = word;
//        }
        Porter2Stemmer::stem(word);
        auto iter = wordMap.emplace(word, 0);
        iter.first->second++;

        // insert word to tree
        // std::vector<IndexEntry> temp;
        // temp.push_back(IndexEntry(word));
        // IndexEntry temp(word);
        // TreeIndex.insert(temp);
//        TreeIndex.insert(temp);
//        IndexEntry test = TreeIndex.getEntry(word);
        //CODE REVIEW COMMENTS (Two Options: Stay same = slower, Choose first option adam provides):
        //DO THIS: you either insert an IndexEntry for every word only after you are done parsing the entire dataset, or after you are done reading in a single file you update the map in each IndexEntry that is already in your AVLTree
        //function need to return integer iand number of words in document as well as and an Index Entry because you need index entry created for that specifically
        //^^^(DONT FORGET TO MAKE PUBLIC: instead of inserting temp, we can create index entry with already created map, and put that index entry into the tree
        //whereever this function is called we should do index entries there instead


        // IndexEntry temp(word);
        // TreeIndex.insert(temp);
        // const IndexEntry& test = TreeIndex.getEntry(word);

        // add doc to entry
//        test.addDocToIdxEntry(doc.title);
    }

    //now we can fill the AVLTree with the wordMap
    for (auto& wordItem: wordMap) {
        TreeIndex.insertEntry(IndexEntry(wordItem.first, doc.uuid, wordItem.second));
    }
}

void IndexHandler::addPersons(const Document& doc){
    for (auto& name: doc.people) {
        PeopleTree.insertFilter(FilterEntry(name, doc.uuid));
    }
}

void IndexHandler::addOrgs(const Document& doc){
    for (auto& name: doc.orgs) {
        OrgsTree.insertFilter(FilterEntry(name, doc.uuid));
    }
}

// function get top 50 words will output all words in TreeIndex along with their number of appearances. it first calles treeindex's ouuutput function to print all words inn TreeIndex then it gets all words in TreeIndex as a vector of IndexEntry objects. It sorts this vector sin descrnng order based off of each objects number of documents using a custom comparator strutct
void IndexHandler::getTop50Words() {
    TreeIndex.prettyPrintTree(); // output tree
    vector<IndexEntry> allWords = TreeIndex.getEntries(); // get vector of all words
    cout << "\tWord - # of Appearances" << endl; // seeing how many times each word appears
    sort(allWords.begin(), allWords.end(), [](const IndexEntry& word1, const IndexEntry& word2) {
        return word1.getNumDocs() > word2.getNumDocs();
    });
    int i = 0; // counter
    for (IndexEntry& e : allWords) { // print out the top 50 words
        if (i > 49) // if we have printed out 50 words, break
            break; // break out of loop
        cout << "\t" << i + 1 << ". " << e.getWord() << " - " << e.getNumDocs() << endl;
        i++; // increment counter
    }
    TreeIndex.clearElements();
    //
}

set<string> IndexHandler::getDocsFromTree(const string& word) {
    IndexEntry result = TreeIndex.getEntry(word);  // get the index entry
//    if (result.getDocNamesSet().empty()) {                       // if the word is not in the tree, return an empty set
//        // cout<<"No docs for that word found ("<<word<<") \n";
//        return set<string>();
//    } else {                                                      // if the word is in the tree, return the set of docs
//        // cout<<"Docs for that word found ("<<word<<") \n";
//        // cout<<result<<endl;
//        return result.getDocNamesSet();
//    }
    set<string> answer;
    for (auto& element : result.uuidMap) {
        answer.insert(element.first);
    }
    return answer;
}


unordered_set<string> IndexHandler::getDocFromPerson(const string& word) {
    auto it = PeopleTree.getEntry(word);
    if(!(it == FilterEntry())){
        return it.uuidSet;
    }
    else{
        unordered_set<string>emptySet;
        return emptySet;
    }
}

unordered_set<string> IndexHandler::getDocFromOrgs(const string& word) {
    auto it = OrgsTree.getEntry(word);
    if(!(it == FilterEntry())){
        return it.uuidSet;
    }
    else{
        unordered_set<string>emptySetTwo;
        return emptySetTwo;
    }
}

//CODE REVIEW COMMENT: change all to unordered set

void IndexHandler::loadPersistenceFileIndexPersons() {
    ifstream file("/home/pc/persistence_index/personsindex.txt");

    if (!file.is_open()) {  // if the file is open
        cout << "Persistence file (PERSONS) not found." << endl << endl;  // if the file is not open, print out that the file is not open
    }
    string line;
    while (getline(file, line)) {  // while there are lines in the file
        stringstream ss(line);     // put the line in a string stream

        // get the word
        string word;
        getline(ss, word, ',');

        string docs;
         while(getline(ss,docs,',')){
             PeopleTree.insertFilter(FilterEntry(word, docs));
         }
    }
    file.close();
}



void IndexHandler::loadPersistenceFileIndexOrgs() {             // load the orgs file
    ifstream file("/Users/trevorgicheru/persistence_index/orgsindex.txt");  // open the file
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);

            // get the word
            string word;
            getline(ss, word, ',');

            string docs;
            while (getline(ss, docs, ',')) {
                OrgsTree.insertFilter(FilterEntry(word, docs));
             }
            }
            file.close();
        } else {
            cout << "Persistence file (ORGS) not found." << endl
                 << endl;
        }
    }


// loading files from
    void IndexHandler::loadPersistenceFileIndexWords() {
        ifstream file("/Users/trevorgicheru/persistence_index/wordindex.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);

                // get the word
                string word;
                getline(ss, word, ',');

                // get # docs
                string numDocs;
                int numDocsInt;
                getline(ss, numDocs, ',');
                numDocsInt = stoi(numDocs);
                IndexEntry idx(word);

                string fileName, freqStr;
                int freq;
                for (int i = 0; i < numDocsInt; i++) {
                    getline(ss, fileName, ',');
                    getline(ss, freqStr, ',');
                    freq = stoi(freqStr);

//                idx.docNameSetInsert(fileName);         // insert the file name into the set
                    idx.docNamesMapInsert(fileName, freq);  // insert the file name and the frequency into the map
                }
                TreeIndex.insert(idx);
            }
            file.close();
        } else {
            cout << "Persistence file (WORDS) not found." << endl
                 << endl;
        }
    }

// saving info that can be used for late retrieval
    void IndexHandler::savePersistenceFileIndexPersons() {
        ofstream open("/home/pc/persistence_index/personsindex.txt");
        PeopleTree.prettyPrintTree();
        open.close();
    }
    void IndexHandler::savePersistenceFileIndexOrgs() {
        ofstream open("/home/pc/persistence_index/orgsindex.txt");
        OrgsTree.prettyPrintTree();
        open.close();
    }
    void IndexHandler::savePersistenceFileIndexWords() {
        ofstream open("/home/pc/persistence_index/wordindex.txt");
        TreeIndex.prettyPrintTree();
    }

// resetting tree
    void IndexHandler::clear() {
        TreeIndex.clearElements();
        numWords = 0;
        treeSize = 0;

        // todo clear hash tables
        //  hashTableOrgs.clear();
        //  hashTablePersons.clear();
    }
