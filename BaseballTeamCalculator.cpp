/*
 *  Anthony Ronca
 *  CIT 133 - 3001
 *  Nov 14 2018
 *
 *  Receives file input for a baseball team with up to 40 players
 *  Outputs the stats of those players into a user specified file
 *
 *
 *  VARIABLES USED:
 *     fileName         -   User input for desired file to read
 *     fileNameOut      -   User input for save file name
 *     players          -   The amount of players on the team, used for averaging
 *     year             -   Year of the team
 *     backwardName     -   Reversed version of team name
 *     numOfStats
 *
 *  ARRAYS USED:
 *     names[]          -   Player's names
 *     battAvg[]        -   Batting stat for each player
 *     homeRuns[]       -   Each player's homeruns count
 *     strikeOuts[]     -   Amount of player's strikeouts
 *     walks[]          -   Player's walk stats
 *     stats[]          -   holds battAVG, Homeruns, Strikeouts, and walks for team
 *
 */


#include <iostream>
#include <fstream>  // input output file
#include <iomanip>  // setprecision

using namespace std; // cin, cout


string stringFormat(string teamName); // returns backwardName

void readData(ifstream &file, string names[], double battAvg[], int homeRuns[],
              int strikeOuts[], int walks[], int players, double stats[] );

void processData(double battAvg[], int homeRuns[],
                 int strikeOuts[], int walks[], int players, double stats[]);

void writeData(ofstream &file, string teamName, string backwardName, int year, double stats[], int numOfStats );


int main(){

    static string fileName;     //  Input file name
    static string fileNameOut;  //  Output file name
    int players;                //  Num of players on team
    int year;                   //  Year of team assembled
    string backwardName;        //  Reversed team name
    int numOfStats = 0;         //  Stores amount of stats
    string names[40];           //  stores player names MAX 40
    double battAvg[40];         //  stores player batting average MAX 40
    int homeRuns[40];           //  stores player home runs MAX 40
    int strikeOuts[40];         //  stores player strike outs MAX 40
    int walks[40];              //  stores player walks MAX 40
    double stats[40];           //  stores teams overall stats MAX 40

    cout << "Enter the name of a file: ";
    cin >> fileName; // GET fileName

    static ifstream infile; // Open input file
    infile.open(fileName.c_str()); // Open file based on user input

    static ofstream outfile; // Open output file

    cout << "\n" << "Enter name of a save file: ";
    cin >> fileNameOut; // GET fileNameOut;

    outfile.open(fileNameOut.c_str()); // Open output file using user input

    string teamName;
    // Load initial name and year
    infile >> teamName >> year >> players;


    backwardName = stringFormat(teamName);

    // Read parameters from file
    readData( infile, names, battAvg, homeRuns,
             strikeOuts,  walks,  players,  stats );

    // Process arrays and calculate
    processData( battAvg,  homeRuns,
             strikeOuts,  walks,  players,  stats);

    // Output calculated data
    writeData( outfile, teamName, backwardName, year, stats, numOfStats );


    infile.close();
    outfile.close();

    return 0;

} // END Main

// Takes a team name and returns it backwards
string stringFormat(string teamName){


    char nameArray[40];
    string backwards;
    int backCount = 0;
    int count = 0;
    string backwardName;

    // Store each character of teamName string into an array
    for(int i = 0; i <= teamName.length(); i++){
        nameArray[i] = teamName[i];
    }

    // Store each element into a variable decrementing from the last character
    for( int i = teamName.length(); i >= 0; i-- ){
        backwards[backCount] = nameArray[i];
        backwardName += backwards[backCount];
    }

return backwardName;

}

// Retrieve data from specified file
void readData(ifstream &file, string names[], double battAvg[], int homeRuns[],
        int strikeOuts[], int walks[], int players, double stats[] ){

    int i = 0;
    static int count = 0;

    // Read through file and store elements in arrays
    while(!file.eof()) {

        file >> names[i] >> battAvg[i] >> homeRuns[i] >> strikeOuts[i] >> walks[i];

        players++;
        i++;

    }
}

// Calculate data
void processData(double battAvg[], int homeRuns[],
                 int strikeOuts[], int walks[], int players, double stats[]){

    double totalBatt = 0;
    double totalHomeRuns = 0;
    double totalStrikeOuts = 0;
    double totalWalks = 0;


    for(int i = 0; i < players; i++){

        // Total up entire array for team stats
        totalBatt += battAvg[i];
        totalHomeRuns += homeRuns[i];
        totalStrikeOuts += strikeOuts[i];
        totalWalks += walks[i];
    }

    // Load stats into separate array as requested
    stats[0] = totalBatt/players;
    stats[1] = totalHomeRuns;
    stats[2] = totalStrikeOuts;
    stats[3] = totalWalks;

}

 // Display calculations
void writeData(ofstream &file, string teamName, string nameBackwards, int year, double stats[], int numOfStats ){

    file << teamName << "," << nameBackwards << ", " << year;

    for ( int i = 0; i < 4; i++){

        file << setprecision(3) << ", " << stats[i];

    }


}

