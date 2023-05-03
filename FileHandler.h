#include "FileHandler.h"
#include "IndexHandler.h"
#include "IndexEntry.h"


using namespace std;

void FileHandler::updateIndex(const string&file){ //updateIndex parses components in string file
    // parses doc
    Document doc(file);
    pathMap[doc.uuid] = file;
    i.addDoc(doc);

    // add persons
    i.addPersons(doc);
    // add orgs
    i.addOrgs(doc);
}

//queryTreeWord takes in string words, integers count, and integer type
void FileHandler::queryTreeAndWords(){
    if(andWords.empty()){
        return;
    }

    auto iter = andWords.begin();
    if(intersect.empty()) {
        intersect.merge(i.getDocsFromTree(*iter));
        iter++;
    }
    while(iter != andWords.end()){
        set<string> copy = intersect;
        intersect.clear();
        set<string> tempy = i.getDocsFromTree(*iter);
        set_intersection(tempy.begin(),tempy.end(),copy.begin(),
                         copy.end(),inserter(intersect,intersect.begin()));
        iter++;
    }
}

void FileHandler::queryTreeOrWords(){
    if(orWords.empty()){
        return;
    }

    for (auto& word: orWords) {
        set<string> tempy = i.getDocsFromTree(word);
        intersect.merge(tempy);
    }
}

//queryTree will then update the word and get documents for the word then checks if this i the first word being checked or not
void FileHandler::queryTreeNotWords() {
    if(notWords.empty()){
        return;
    }

    auto iter = notWords.begin();
    while(iter != notWords.end()){
        set<string> copy = intersect;
        set<string> toRemove;
        set<string> tempy = i.getDocsFromTree(*iter);
        set_intersection(tempy.begin(),tempy.end(),copy.begin(),
                         copy.end(),inserter(toRemove,toRemove.begin()));
        for (auto& notUUID: toRemove) {
            intersect.erase(notUUID);
        }
        iter++;
    }
}


void FileHandler::queryPersons(){
    if(people.empty()){
        return;
    }

    auto iter = people.begin();
    if(intersect.empty()) {
        unordered_set<string> tempUnoSet = i.getDocFromPerson(*iter);
        set<string> tempy(tempUnoSet.begin(), tempUnoSet.end());
        intersect.merge(tempy);
        iter++;
    }
    while(iter != people.end()){
        unordered_set<string> tempUnoSet = i.getDocFromPerson(*iter);
        set<string> tempy(tempUnoSet.begin(), tempUnoSet.end());
        set<string> copy = intersect;
        intersect.clear();
        set_intersection(tempy.begin(),tempy.end(),copy.begin(),
                         copy.end(),inserter(intersect,intersect.begin()));
        iter++;
    }
}

void FileHandler::queryOrgs(){
    if(organs.empty()){
        return;
    }

    auto iter = organs.begin();
    if(intersect.empty()) {
        unordered_set<string> tempUnoSet = i.getDocFromOrgs(*iter);
        set<string> tempy(tempUnoSet.begin(), tempUnoSet.end());
        intersect.merge(tempy);
        iter++;
    }
    while(iter != organs.end()){
        unordered_set<string> tempUnoSet = i.getDocFromOrgs(*iter);
        set<string> tempy(tempUnoSet.begin(), tempUnoSet.end());
        set<string> copy = intersect;
        intersect.clear();
        set_intersection(tempy.begin(),tempy.end(),copy.begin(),
                         copy.end(),inserter(intersect,intersect.begin()));
        iter++;
    }
}

void FileHandler::outputResults(){
    top15Sets();
    int k=1;
    if(top15.empty()){
        cout<<"\nNo search results found\n\n";
    }else{
        for(const auto& e: top15){
            if(k>15)
                break;
            Document doc(e.filepath);
            cout<<k<<". "<<doc.site<<endl;
            char esc_char = 27;
            cout<<esc_char<<"[1m"<<doc.title<<esc_char<<"[0m"<<endl;
            cout<<doc.site.substr(0,10)<<" — ";

            k++;
        }
        intersect.clear();
    }
}

void FileHandler::top15Sets(){
    //here is where you initiate the calculation of the intersections
    intersect.clear();
    top15.clear();

    //fill intersect
    queryTreeAndWords();
    queryTreeOrWords();
    queryTreeNotWords();
    queryOrgs();
    queryPersons();

    string word;
    stringstream ss;
    double inverseDocFreq = log(double(numFiles) / intersect.size());
    for(const auto&e:intersect){
        Document doc(pathMap[e]);
        string temp = doc.text;
        // specific metrics for each doc
        int score=0;
        int wordCount=0;

        // get each word
        ss.str(temp);
        while(ss>>word){
            //todo: for `word` lowercase and remove non-alpha
            Porter2Stemmer::stem(word);

            wordCount++;
            if(andWords.find(word) != andWords.end() || orWords.find(word) != orWords.end())
                score++;
        }
        double tf_idf = double(score) / double(wordCount) * inverseDocFreq;
        docWithMetrc obj(e,tf_idf, pathMap[e]);
        top15.insert(obj);

        ss.clear();
    }
}

void FileHandler::getTop50Words(){
    i.getTop50Words();
}

void FileHandler::clear() {
    intersect.clear();
    top15.clear();
    numFiles=0;

    i.clear();
}

void FileHandler::viewDoc(const int choice) {
    int k=1;
    stringstream ss;
    for(const auto& e: top15){
        if(k==choice){
            Document doc(pathMap[e.docName]);
            char esc_char = 27;
            cout<<endl;

            cout<<doc.site<<endl;
            cout<<esc_char<<"[1m"<<doc.title<<esc_char<<"[0m"<<endl;
            cout<<doc.site.substr(0,10)<<" — ";
            string temp = doc.text;

            string word;
            stringstream ss(temp);
            int i=1;
            while(ss>>word){
                 if(i%18==0){
                     cout<<"\n";
                     break;
                 }
                cout<<word<<" ";
                ++i;
            }
            i=1;
            while(ss>>word){
                if(i%20==0){
                    cout<<"\n";
                }
                cout<<word<<" ";
                i++;
            }
            cout<<endl<<endl;
        }

        k++;
    }
}
