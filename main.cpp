#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdlib.h>  // OR #include <bits/stdc++.h>
#include <string>
using namespace std;

// Command line AutoMap.exe /man (or any too small number of argument, included zero!) for help.
// Command line AutoMap.exe map.txt 5 "a"=1 "b"=2 "c"=3 "d"=4 "e"=5 "f"=5 for normal usage.

string mixable(string word) // Source corrected from: https://openclassrooms.com/courses/programmez-avec-le-langage-c/tp-le-mot-mystere
{
    string mix;
    int position(0);
    while (word.size() != 0)
    {
        position = rand() % word.size();
        mix += word[position];
        word.erase(position, 1);
    }
    return mix;
}

int helpAutoMap()
{
    cout << "This program makes a pseudo-random rectangular map for your video game." << endl;
    cout << "Command line only. Arguments are:" << endl;
    cout << "Name of the software." << endl;
    cout << "Name of the final file." << endl;
    cout << "Number of the columns of the file." << endl;
    cout << "Character you want in the file \"=\" it\'s number (reapeated)." << endl << endl;
    cout << "For example, you may have for:" << endl;
    cout << "AutoMap.exe map.txt 15 \"A\"=7 \"Z\"=4 \"#\"=77" << endl << endl;
    cout << "######Z########" << endl;
    cout << "###Z#######Z###" << endl;
    cout << "#####AAA#######" << endl;
    cout << "############Z##" << endl;
    cout << "###A###A#######" << endl;
    cout << "#####A#####A###" << endl << endl;
    cout << "Version alpha: do NOT use multiple characters, special character like \", space, smiley... " << endl;
    cout << "If you need them: replace after." << endl;
    cout << "https://github.com/RedGuff/AutoMap" << endl;
    return 0;
}

int main(int argc, char* argv[]) // Arguments: file.txt, Number of columns, each symbol and it's number.
{
    srand (time(NULL)); /* initialize random seed: */
    if (argc < 4) // Working, for almost every help needed, like /man, /?, /help, missing arguments...
    {
        helpAutoMap();
        return 1; // Error help.
    }
    else
    {
        /*      cout << "TESTS:{" << endl;
                cout << argc << endl;
                for (int argument=0; argument<argc ; argument++)  // to test normal.        {
                {
                    cout << "argv[" <<argument<<"] = " << argv[argument] << endl; // Test ok.
                }
        */
        string mot=""; // It will be mixed later.
        for (int argument=3; argument<argc ; argument++)  // For each letter wanted only...
        {
            // cout << "argv[" <<argument<<"] : " ; // Test ok.
            // Each argument of this loop can be separated in 3 parts (before =, =, after =), for example for "a"=1...
            string numberOfThatLetterString=""; // The number of "a" to write, for example, but in string.
            string thatArgument=argv[argument]; // "a=1" for exemple.
            string equality="=";
            // cout << thatArgument.substr(0,(thatArgument.find(equality))) << " = " ;
            numberOfThatLetterString=thatArgument.substr(thatArgument.find(equality) + 1);
            int numberOfThatLetter=atoi(numberOfThatLetterString.c_str()); //	int i = atoi(s.c_str()); https://github.com/khaledalam/YouTube_CPP_codes/blob/master/StringToInt.cpp
            // cout << numberOfThatLetter << endl; // Tests ok.
            // cout << numberOfThatLetter<< " " ; // Tests ok.
            for (int i=0; i< numberOfThatLetter; i++ )
            {
              mot=mot+thatArgument.substr(0,(thatArgument.find(equality)))  ;
            // inputLineChar[argument-3]=thatArgument.substr(0,(thatArgument.find(equality))) ; // It's possible to have special variable, but it's useless for this small number of parameters.
            // inputLineNumber[argument-3]=numberOfThatLetter;
            }
        }
        // cout << mot << endl; // Tests ok.
        string motMixed=mixable(mot);
        // cout << motMixed;
        ofstream myfile;
        myfile.open (argv[1]);
        if (!myfile.is_open()) // Error file.
        {
            cerr << "Unable to open file!";   // Err of file? Help needed:
            helpAutoMap();
            return 2; // Error file.
        }
        else // File ok.
        {
            int argvTwo =atoi(argv[2]); // The number of column wanted.
            for (int letter=0; letter<motMixed.length() ; letter++)
            {
                myfile << motMixed[letter];
                if (((letter +1) % argvTwo)==0) // Number of column reached. // (letter +1) because init letter is 0.
                {
                    myfile << "\n";
                }
            }
            myfile.close();
        }
    }
    return 0; // Ok.
}
