#include <iostream>
using namespace std;
class QueryEngine
{
    private:
        string Word;
    public:
        void changeWord(const string&);
        void getStemmedWord();
};