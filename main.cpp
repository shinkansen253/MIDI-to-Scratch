#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;



int main()
{
    string trash;
    
    string fileName;
    cout << "Enter text file name: ";
    cin >> fileName;
    
    ifstream inFile(fileName.c_str());
    ofstream notesFile("gen_notes.txt");
    ofstream timesFile("gen_times.txt");
    
    if(!inFile.is_open())
    {
        cout << "Failed to open file " << fileName << endl;
        cin.get();
        return 0;
    }
    
    int clocksPerBeat;
    inFile >> trash >> trash >> trash >> clocksPerBeat;
    
    string line;
    while(getline(inFile, line))
    {
        if(line.find("On") != string::npos)
        {
            double rawClock;
            string rawNote;
            istringstream inString(line.c_str());
            inString >> rawClock >> trash >> trash >> rawNote;
            
            timesFile << rawClock / clocksPerBeat << endl;
            notesFile << rawNote.substr(2, rawNote.length() - 2) << endl;
        }
    }
    
    cout << "SUCCESS: Your song is located in two lists: gen_notes.txt & gen_times.txt" << endl;
    inFile.close();
    notesFile.close();
    timesFile.close();
    
    return 0;
}