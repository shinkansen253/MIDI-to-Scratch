// Use http://flashmusicgames.com/midi/mid2txt.php to convert MIDI to TXT
//Accounts for multiple tracks

#include <iostream>
#include <vector>
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

	if (!inFile.is_open())
	{
		cout << "Failed to open file " << fileName << endl;
		cin.get();
		cin.get();
		return 0;
	}

	ofstream notesFile("gen_notes.txt");
	ofstream timesFile("gen_times.txt");
	vector<int> notesVect;
	vector<double> timesVect;

	int clocksPerBeat;
	inFile >> trash >> trash >> trash >> clocksPerBeat;

	string line;
	int i;

	getline(inFile, line);

	while (getline(inFile, line))
	{
		if (line.find("TrkEnd") != string::npos)
		{
			i = 0;
		}
		else if (line.find("On") != string::npos)
		{
			double rawClock;
			string rawNote;
			istringstream inString(line.c_str());
			inString >> rawClock >> trash >> trash >> rawNote;

			double beat = rawClock / clocksPerBeat;
			int note = stoi(rawNote.substr(2, rawNote.length() - 2));

			if (timesVect.size() > 0)
			{
				while (i < timesVect.size() && beat >= timesVect.at(i))
				{
					i++;
				}
				
				
				timesVect.insert(timesVect.begin() + i, beat);
			    notesVect.insert(notesVect.begin() + i, note);
			}
			else
			{
			    timesVect.push_back(beat);
			    notesVect.push_back(note);
			}

			
		}
	}

	for (unsigned j = 0; j < timesVect.size(); ++j)
	{
		notesFile << notesVect.at(j) << endl;
		timesFile << timesVect.at(j) << endl;
	}

	cout << "SUCCESS: Your song is located in two lists: gen_notes.txt & gen_times.txt" << endl;
	inFile.close();
	notesFile.close();
	timesFile.close();

	cin.get();
	cin.get();
	return 0;
}
