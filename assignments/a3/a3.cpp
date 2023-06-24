// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Sahir Sood!>
// St.# : <301462135>
// Email: <ssa434@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not #include any other files!
//
#include "Announcement.h"
#include "JingleNet_announcer.h"
#include "Queue_base.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;





class Queue : public Queue_base<Announcement>
{
    struct Node
    {
        Announcement message;
        Node* next;
    };
    Node*front,*rear;


    public:

        Queue(){}

        Queue()

}












//
// argc is the number of command-line arguments, i.e. the size of argv
//
// argv is an array of strings, where each string is a command-line argument;
//      argv[0] is the program name that is run, e.g. "./getline_demo"

int main(int argc, char *argv[])
{
    // Check that the user provided a filename.
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        //
        // Returning a non-zero value from main indicates the program ended
        // abnormally. We don't care about main return values, but in some cases
        // they are useful. If this program was used as part of a shell script,
        // then the script might check this return value in an if-statement.
        //
        return 1; 
    }

    //
    // Read the contents of the file named by argv[1], and print each line.
    //
    string filename = argv[1];

    ifstream infile(filename);
    string line;


    





    string command;
    string name;
    string title;
    string message;


    while (getline(infile, line))
    {
      size_t spacePos = line.find(' ');
      command = line.substr(0, spacePos);
      string params = line.substr(spacePos + 1);

      if(command == "SEND"){
        spacePos = params.find(' ');
        name = params.substr(0,spacePos);
        params = params.substr(spacePos +1);

        spacePos = params.find(' ');
        title = params.substr(0,spacePos);
        params = params.substr(spacePos +1);

        message = params;

        Rank announcementRank;
        if (title == "santa")
            announcementRank = Rank::SANTA;
        else if (title == "reindeer")
            announcementRank = Rank::REINDEER;
        else if (title == "elf2")
            announcementRank = Rank::ELF2;
        else if (title == "elf1")
            announcementRank = Rank::ELF1;
        else if (title == "snowman")
            announcementRank = Rank::SNOWMAN;
        else
        {
            cout << "Invalid rank: " << title << endl;
            continue;
        }

        Announcement announce()

      }
      else if(command == "Remove_ALL"){

      }
      else if(command == "PROMOTE_ANNOUNCEMENTS"){

      }
      else if(command == "ANNOUNCE"){

      }
    }

} // main
