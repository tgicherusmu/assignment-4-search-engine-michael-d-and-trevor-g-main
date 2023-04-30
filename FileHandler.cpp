#include "FileHandler.h"
#include "IndexHandler.h"
#include "IndexEntry.h"


using namespace std;

void FileHandler::updateIndex(const string&file){ //updateIndex parses components in string file
    // parses doc
    Document doc(file);
    i.addDoc(doc);

    // add persons
    i.addPersons(doc);
    // add orgs
    i.addOrgs(doc);
}

//queryTreeWord takes in string words, integers count, and integer type
void FileHandler::queryTreeWords(string word, int count, const int& type){
    // update word
    q.changeWord(word);
    string query = q.getStemmedWord();

    // get docs for word
    set<string> temp = i.getDocsFromTree(query);

    // check if this is the first word being searched
    if(count!=0){
        // check if set is empty
        if(temp.empty()){
            // clear intersect if AND search
            if(type==1){
                intersect.clear();
            }
            return;
        }

        if(type==1){
            // copy intersect set and clear to be able to form new intersect
            set<string> temp2 = intersect;
            intersect.clear();

            // get intersection of old and new set
            set_intersection(temp.begin(),temp.end(),temp2.begin(),
                             temp2.end(),inserter(intersect,intersect.begin()));
        } // OR
        else if(type==2){
            // insert all elements into main set
            for(const auto& e: temp){
                intersect.insert(e);

            }
        }

    }
    // first word being searched
    else{
        // assign set to intersect
        if(!temp.empty()){
            intersect = temp;
        }
    }


}

//queryTree will then update the word and get documents for the word then checks if this i the first word being checked or not
void FileHandler::queryTreeNotWords(const string& word) {

    // update word
    q.changeWord(word);
    string query = q.getStemmedWord();

    // get docs
    set<string> temp = i.getDocsFromTree(query);

    // check if set is empty
    if (temp.empty()) {
        return;
    } else {
        // copy intersect set and clear old
        set<string> temp2 = intersect;
        intersect.clear();

        // remove docs with word (order matters)
        set_difference(temp2.begin(), temp2.end(), temp.begin(),
                       temp.end(), inserter(intersect, intersect.begin()));
    }
}


void FileHandler::queryPersons(const string&person){
    // get set
    unordered_set<string> temp = i.getDocFromPerson(person);
    unordered_set<string> emptySet;
    // check if set is empty
    if(temp==emptySet){
        intersect.clear();
    }else{
        // copy intersect set and clear old
        set<string> temp2 = intersect;
        intersect.clear();

        // intersect
        set_intersection(temp.begin(),temp.end(),temp2.begin(),
                         temp2.end(),inserter(intersect,intersect.begin()));
    }
}

void FileHandler::queryOrgs(const string&orgs){
    // get set
    unordered_set<string> temp = i.getDocFromOrgs(orgs);
    unordered_set<string> emptySet;
    // check if set is empty
    if(temp==emptySet){
        intersect.clear();
    }else{
        // copy intersect set and clear old
        set<string> temp2 = intersect;
        intersect.clear();

        // intersect
        set_intersection(temp.begin(),temp.end(),temp2.begin(),
                         temp2.end(),inserter(intersect,intersect.begin()));
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
            Document doc(e.docName);
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

    string MainWord = mainWord;
    Porter2Stemmer::trim(MainWord);
    Porter2Stemmer::stem(MainWord);
    string word;
    stringstream ss;
    double inverseDocFreq = log(double(numFiles) / intersect.size());
    for(const auto&e:intersect){
        Document doc(e);
        string temp = doc.text;
        // specific metrics for each doc
        int score=0;
        int wordCount=0;

        // get each word
        ss.str(temp);
        while(ss>>word){
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);

            wordCount++;
            if(word==MainWord)
                score++;
        }
        double tf_idf = double(score) / double(wordCount) * inverseDocFreq;
        docWithMetrc obj(e,tf_idf);
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
    mainWord="";

    i.clear();
}

void FileHandler::viewDoc(const int choice) {
    int k=1;
    stringstream ss;
    for(const auto& e: top15){
        if(k==choice){
            Document doc(e.docName);
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
