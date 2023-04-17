// insert stopword vector
// add an unordered map called hashed word that maps strings to strings
// make a function called addPerson that takes in nameOfDoc and a list of strings called persons. it should iterate through each string in the list and insert it into a hashtable called hashTablePersons along with document anmes
// addOrds function will take two arguments, a string called nameOfDoc and a list of strings called persons. It iterates through each string in the list and inserts it into a hash table called hashTableOrds along with the document name
// the function addDoc takes two arguments a string called nameOfDoc and a string called persons. it iterates through seach string and inserts it into the hashtable hashTableOrgs along with the ducment names
// a dunction addDoc will take two arguemnsta a tring called nameOfDoc and a string called DocText. It extracts all the words from the text using stringstream then checks to see if the word is a stop word
// if the word is not in stoplist then it increments a counter called numWords then checks to see if the word has already been hashed and if its been hashed then it replaces word with hashed calue if it has not been hashed then it gets the stemmed version of the word via using Porter2Stemmmer library
// function get top 50 words will output all words in TreeIndex along with their number of appearances. it first calles treeindex's ouuutput function to print all words inn TreeIndex then it gets all words in TreeIndex as a vector of IndexEntry objects. It sorts this vector sin descrnng order based off of each objects number of documents using a custom comparator strutct
#include "IndexHandler.h"
// list of stop words
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

unordered_map<string, string> theHashedWords;
// void IndexHandler::addPersons(const string&nameOfDoc, list<string> persons){
//     for (auto it=persons.begin(); it != persons.end(); ++it)
//         hashTablePersons.insert(*it, nameOfDoc);
// }
// void IndexHandler::addOrgs(const string&nameOfDoc, list<string> persons){
//     for (auto it=persons.begin(); it != persons.end(); ++it)
//         hashTableOrgs.insert(*it, nameOfDoc);
// }

void IndexHandler::addDoc(const string& nameOfDoc, const string& docText) {
    // put text of file in ss
    stringstream ss(docText);

    // extract the words
    string word;
    while (ss >> word) {
        // see if word is in stoplist
        auto it = theStopWords.find(word);  // check if word is in stoplist
        if (it != theStopWords.end()) {     // if it is in the stoplist, continue
            continue;
        }

        // TA Adam E: wouldnt you only want to increment the number of words every time you find a new word? right now, you incremenet for every word you have
        numWords++;  // increment number of words
        // check if word has been hashed
        auto it2 = theHashedWords.find(word);  // check if word is in theHashedWords
        if (it2 != theHashedWords.end()) {     // if it is in theHashedWords, continue
            word = theHashedWords[word];       // set word to the hashed version of the word

        } else {  //
            // get stemmed version of word
            string temp = word;
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            // add to table
            theHashedWords[temp] = word;
            theHashedWords[word] = word;
        }

        // continue if word is empty
        if (word.empty())
            continue;

        // insert word to tree
        // std::vector<IndexEntry> temp;
        // temp.push_back(IndexEntry(word));
        // IndexEntry temp(word);
        // TreeIndex.insert(temp);
        IndexEntry temp(word);
        TreeIndex.insert(temp);
        IndexEntry& test = TreeIndex.getEntry(word);

        // IndexEntry temp(word);
        // TreeIndex.insert(temp);
        // const IndexEntry& test = TreeIndex.getEntry(word);

        // add doc to entry
        test.addDocToIdxEntry(nameOfDoc);
    }
}

void IndexHandler::getTop50Words() {
    TreeIndex.output(); // output tree
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
}

set<string> IndexHandler::getDocsFromTree(const string& word) {
    IndexEntry result = TreeIndex.getElement(IndexEntry(word));  // get the index entry
    if (result.getDocNamesSet().empty()) {                       // if the word is not in the tree, return an empty set
        // cout<<"No docs for that word found ("<<word<<") \n";
        return set<string>();
    } else {                                                      // if the word is in the tree, return the set of docs
        // cout<<"Docs for that word found ("<<word<<") \n";
        // cout<<result<<endl;
        return result.getDocNamesSet();
    }
}

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
        // while(getline(ss,docs,',')){
        //     hashTablePersons.insert(word,docs);
        // }
    }
    file.close();
}
void IndexHandler::loadPersistenceFileIndexOrgs() {             // load the orgs file
    ifstream file("/home/pc/persistence_index/orgsindex.txt");  // open the file
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);

            // get the word
            string word;
            getline(ss, word, ',');

            string docs;
            // while(getline(ss,docs,',')){
            //     hashTableOrgs.insert(word,docs);
            // }
        }
        file.close();
    } else {
        cout << "Persistence file (ORGS) not found." << endl
             << endl;
    }
}

// loading files from
void IndexHandler::loadPersistenceFileIndexWords() {
    ifstream file("/home/pc/persistence_index/wordindex.txt");
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
            IndexEntry idx(word, numDocsInt);

            string fileName, freqStr;
            int freq;
            for (int i = 0; i < numDocsInt; i++) {
                getline(ss, fileName, ',');
                getline(ss, freqStr, ',');
                freq = stoi(freqStr);

                idx.docNameSetInsert(fileName);         // insert the file name into the set
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
    // hashTablePersons.output(open);
    open.close();
}
void IndexHandler::savePersistenceFileIndexOrgs() {
    ofstream open("/home/pc/persistence_index/orgsindex.txt");
    // hashTableOrgs.output(open);
    open.close();
}
void IndexHandler::savePersistenceFileIndexWords() {
    ofstream open("/home/pc/persistence_index/wordindex.txt");
    TreeIndex.print(open);
    open.close();
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
