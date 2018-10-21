#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

class EndOfFileExc : public exception
{
  public:
    string tresc;
    EndOfFileExc(const char* t){
        tresc = t;
    };
    virtual const char* what(){
        return tresc.c_str();
    };
};

class LineReader {
    public:
        ifstream &infile;

    LineReader(ifstream &name): infile(name){}

    string read(){
        string data;
        getline(infile, data);
        if(!infile)
            throw EndOfFileExc("\nEnd of File!\n");
        return data;
    }

    ~LineReader(){
        infile.close();
        cout << "File Closed" << endl;
    }
};

int main(){

    try{
        ifstream infile("Test.txt");
        shared_ptr<LineReader> data = make_shared<LineReader>(infile);
        shared_ptr<LineReader> data2 = data;
        vector<shared_ptr<LineReader>> files;
        for(int i=0; i<2; i++){
            files.push_back(data);
            files.push_back(data2);
        }
        for(auto ptr : files){
            for(int i=0; i<6; i++)
                cout << ptr->read() << endl;
            // data->~LineReader();
        }
        
    }
    catch(EndOfFileExc &er)
    {
        cerr << endl << er.what();
    }
}