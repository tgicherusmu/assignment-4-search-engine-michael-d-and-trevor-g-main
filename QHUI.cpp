#include <iostream>
#include<filesystem>
#include "FileHandler.h"
#include "porter2_stemmer.h"
#include <sstream>
#include <algorithm>
#include<limits>
#include <sys/stat.h>
using namespace std;
namespace fs = std::__fs::filesystem;

FileHandler files;
bool parsed = false;
int avgNumWords=0;
int readInFiles(const string&);
void getSearch();
int main(int argc, char* argv[]) {
    // read in files and create avl tree

    string path;

    int option=0;
    int numOfFiles=0;
    do{
        // output menu system
        cout<<"\nSearch Engine Menu\n";
        cout<<"  1. Load Data Files\n";
        cout<<"  2. Execute Query\n";
        cout<<"  3. Show Stats\n";
        cout<<"  4. Clear Index\n";
        cout<<"  5. Quit\n";
        cout<<"  Enter an option: ";
        cin>>option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(option){

            // create index
            case 1:
                if(!parsed){
                    cout<<"  Enter path to the dataset: ";
                    getline(cin,path);
                    numOfFiles = readInFiles(path);
                }
                else{
                    cout<<"\nFiles already loaded!\n";
                }
                break;
                // output search results
            case 2:
                if(parsed)
                    getSearch();
                else
                    cout<<"\nNo data has been loaded!\n";
                break;
            case 3:
                cout<<"\nSearch Engine Statistics\n";
                cout<<"  Total number of individual articles indexed: "<<numOfFiles<<endl;
                cout<<"  Average number of words indexed per article: "<<avgNumWords<<endl;
                cout<<"  50 most frequent words (stemmed version): "<<endl;
                files.getTop50Words();
                break;

            case 4:if(!parsed){
                    cout<<"\nNo data has been loaded!\n";
                }else{
                    cout<<"\nClearing index..."<<flush;
                    files.clear();
                    cout<<" Complete!\n";

                    // reset vars
                    parsed= false;
                    avgNumWords = 0;
                    numOfFiles = 0;
                }
                break;
            default: option =-1;
        }

    }while(option!=-1);

    return 0;
}
// loop over the files in the directory
int readInFiles(const string& path){
    int totalNumFiles=0;
    // check if path is valid
    struct stat info;
    if( stat( path.c_str(), &info ) != 0 ){
        cout<<"\nFolder not found\n";
        files.setNumFiles(0);
        return 0;
    }else{
        cout<<"\nCreating index..."<<flush;
        for (const auto & entry : fs::recursive_directory_iterator(path)){
            if(!is_directory(entry)){
                string filename = entry.path().string();
                cout<<"Adding file to index ("+ filename<<")"<<endl;
                // update index
                files.updateIndex(filename);
                totalNumFiles++;
            }
        }
        cout<<"Complete!\n";
        parsed = true;
        files.setNumFiles(totalNumFiles);
        return totalNumFiles;
    }
}
void getSearch(){
    // search phrase
    string search;
    cout<<"\nEnter search query: ";
    getline(cin,search);

    //put search phrase into ss
    stringstream ss(search);
    string word;

    //show if the word is an identifier
    int option;
    int count=0;
    int check=1;

    // get every word in the phrase
    while(getline(ss,word,' ')){
        if(word=="AND"){
            // get next word
            getline(ss,word,' ');
            Porter2Stemmer::stem(word);
            files.addAndWord(word);
            option = 0;
        }else if(word=="OR"){
            // get next word
            getline(ss,word,' ');
            Porter2Stemmer::stem(word);
            files.addOrWord(word);

            option = 4;
            check = 2;
        }else if(word=="PERSON"){
            getline(ss,word,' ');
            files.addPerson(word);
            option = 1;
        }else if(word=="ORG"){
            getline(ss,word,' ');
            files.addOrgan(word);
            option = 2;
        }else if(word=="NOT"){
            getline(ss,word,' ');
            Porter2Stemmer::stem(word);
            files.addNotWord(word);
            option = 3;
        }
            // search word
        else{
            //query was not formatted correctly
            cout<<"Your Query was not formatted correctly.";
            cout<<"Would you like to search again? (y/n): ";
            char choice;
            cin>>choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(choice =='y'||choice =='Y'){
                getSearch();
            }

//            if(count==0) {
//                Porter2Stemmer::stem(word);
//                files.setMainWord(word);
//            }
//            // AND
//            if(check==1)
//                option = 0;
//                // OR
//            else {
//                option = 4;
//            }
        }

//        switch(option){
//            // AND
//            case 0:{
//                Porter2Stemmer::stem(word);
//                files.queryTreeWords(word, count, 1);
//                break;
//            }
//                // OR
//            case 4:{
//                Porter2Stemmer::stem(word);
//                files.queryTreeWords(word, count, 2);
//                break;
//            }
//                // get next word if it's an identifier
//            case 1:{
//                // can't use alone
//                Porter2Stemmer::stem(word);
//                getline(ss,word,' ');
//                //files.queryHashPersons(word);
//                break;
//            }
//            case 2:{
//                Porter2Stemmer::stem(word);
//                getline(ss,word,' ');
//                //files.queryHashOrgs(word);
//                break;
//            }
//            case 3:{
//                Porter2Stemmer::stem(word);
//                getline(ss,word,' ');
//                //files.queryTreeNotWords(word);
//                break;
//            }
//        }
        count++;
    }
    // output the result
    //files.outputIntersect();
    files.outputResults();

    cout<<endl<<"Enter the number of the document to view it,"
                "\nor enter 0 to return to the main menu: ";
    int see;
    cin>>see;
    if(see!=0 || see>15)
        files.viewDoc(see);
    // ask user if they want to search again
    char repeat;

    files.clearTop15();

    cout<<"Would you like to search again? (y/n): ";
    cin>>repeat;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(repeat=='y'||repeat=='Y'){
        getSearch();
    }
}
