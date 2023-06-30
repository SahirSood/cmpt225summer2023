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

//Queue class that uses a linked list and holds annoucements objects in each node
class Queue : public Queue_base<Announcement>
{
    //initialization of the node struct
    struct Node
    {
        Announcement announcing;
        Node* next;
        
        //struct constructor to allow initialization of the node
        Node(const Announcement &a, Node *n) : announcing(a), next(n) {} 
        
    };
    //varaibles for the front and end of queue
    //size varaible, amount of nodes in the queue
    Node*begin,*rear;
    int sz;

    public:
        //Constructor, sets queue to empty by initializing size to 0 and front/back pointers to null
        Queue() : begin(nullptr), rear(nullptr), sz(0) {}

        //Destructor: Deleting each node with a temp pointer as it iterates through the list
        ~Queue(){
            Node* cur = begin;
            while (cur != nullptr) {
                Node* temp = cur;
                cur = cur->next;
                delete temp;
            }
}
        //Returns sz varaible that we adjust using other functions
        int size()const{
            return sz;
        }

        //Add node to the back of the queue(enters line)
        void enqueue(const Announcement &annouce){
            //create new node using struct constructor
            Node* temp = new Node(annouce,nullptr);
            //When rear==NULL the struct is empty
            //Adding one node will result in the front AND back to equal newnode
            if (rear==NULL){
                begin = rear = temp;
                sz++;   
                return;
            }
            //if size > 1 we just add node to the back of queue
            //change rear pointer to new node
            rear->next = temp;
            rear = temp;
            
            //increment size
            sz++;
        }
        //returns the announcement at the front of the queue
        const Announcement &front()const{
            return begin->announcing;
        }

        //removes the Announcement at the front of the queue(exits line)
        void dequeue(){
            //if the queue is empty, returns an error.
            if(sz == 0){
                throw runtime_error("dequeue: queue is empty");
            }
            Node* temp = begin;
            begin = begin->next;
            
            //if after removing there is no one in the queue, rear pointer assigned to nullptr
            if(begin == nullptr){
                rear = nullptr;
            }
            //decrement size
            sz--;
            delete temp;
        }
        
};

//Jinglenet System class that holds all 5 queues.
//contains needed functions that modifies the queue.

class Jinglenet
{
    private:
        
        Queue santa;
        Queue reindeer;
        Queue elf1;
        Queue elf2;
        Queue snowman;

    //Depending on the rank passed trhough we return a pointer to the corresponding queue.
    Queue* queueswitch(int i){
        if(i==1){
            return &snowman;
        }
        if(i==2){
            return &elf2;
        }
        if(i==3){
            return &elf1;
        }
        if(i==4){
            return &reindeer;
        }
        if(i==5){
            return &santa;
        }
        return nullptr;
    }
    //Function that announces ONLY the first non empty queue in order of Rank
    void announcing(){
        if(santa.size()!=0){
            jnet.announce(santa.front());
            santa.dequeue();
            return;
        }
        else if(reindeer.size()!=0){
            jnet.announce(reindeer.front());
            reindeer.dequeue();
            return;
        }
        else if(elf2.size()!=0){
            jnet.announce(elf2.front());
            elf2.dequeue();
            return;
        }
        else if(elf1.size()!=0){
            jnet.announce(elf1.front());
            elf1.dequeue();
            return;
        }
        else if(snowman.size()!=0){
            jnet.announce(snowman.front());
            snowman.dequeue();
            return;
        }
        else{
            return;
        }
    }   
    public:    
        //Default constructor and Destructor
        Jinglenet(){}
        ~Jinglenet(){}

        //When called it enqueues the annoucement to corresponding queue based off the passed rank
        void send(string name, Announcement data){
            if(name == "santa"){
                santa.enqueue(data);
            }
            if(name == "reindeer"){
                reindeer.enqueue(data);
            }
            if(name == "elf1"){
                elf1.enqueue(data);
            }
            if(name == "elf2"){
                elf2.enqueue(data);
            }
            if(name == "snowman"){
                snowman.enqueue(data);
            }
        }

        //Takes a senders name, and goes through each queue removing any annoucement from the sender.
        void clear(string name){
            Queue* QueuePointer = nullptr;
            Queue temp;

            //Iterating through 1-5 for the 5 different queues
            for(int i =1;i<=5;i++){
                // Sets pointer to a different queue based on the Rank #i
                QueuePointer = queueswitch(i);
                //Until the queue is emtpy we move Nodes to a temporary queue
                //We ignor any nodes with the same sender as the one passed as a paramater.
                while(QueuePointer->size()!=0){
                   
                   //stores the first senders  name and the actual annoucements to varaibles
                    string peekName = QueuePointer->front().get_sender_name();
                    Announcement peekAnnounce = QueuePointer->front();

                    //When the sender at the front is the same as our desired sender
                    //Delete it from the Queue
                    //If it is a different sender we will also enqueue it in our temp queue
                    if(peekName == name){
                        QueuePointer->dequeue();
                    }
                    else{
                        temp.enqueue(peekAnnounce);
                        QueuePointer->dequeue();
                    }
                }

                //Temp queue is in reverse order, put everything back in original queue
                //Original queue will now be in original order without instances of sender
                while(temp.size()!=0){
                    Announcement peekAnnounce = temp.front();
                    QueuePointer->enqueue(peekAnnounce);
                    temp.dequeue();
                }
            }
        }

        //Promotes all annoucmenets from a sender to the next higheghest rank
        void promote(string name){
            Queue temp;
            Queue* QueuePointer =nullptr;
            Queue* PromotionPointer =nullptr;

            //iterates through ranks 1-4, ignoring Santa since it is already highest rank
            for(int i=1;i<=4;i++){

                //Pointers set to current rank and the rank we wish to promote to 
                QueuePointer = queueswitch(i);
                PromotionPointer = queueswitch(i+1);

                //Iterates through every node in the selected queue
                while(QueuePointer->size()!=0){
                    
                    string peekName = QueuePointer->front().get_sender_name();
                    Announcement peekAnnounce = QueuePointer->front();

                    //if the sender at the front of the queue is the same as our desired sender
                    //We enqueue the annoucement to the next rank
                    if(peekName == name){
                        PromotionPointer->enqueue(peekAnnounce);
                        QueuePointer->dequeue();
                    }

                    //When senders do not match, we enqueue the annoucement to our temp queue
                    else{
                        temp.enqueue(peekAnnounce);
                        QueuePointer->dequeue();
                    }
                }

                //Temp queue is in reverse order, put everything back in original queue
                //Original queue will now be in original order without instances of sender
                while(temp.size()!=0){
                    Announcement peekAnnounce = temp.front();
                    QueuePointer->enqueue(peekAnnounce);
                    temp.dequeue();
                }
            }
        }

        //annoucenes the next n annucements
        void announce(string number){
            //turns passed string into an int
            int n = stoi(number);
            int i=1;
            while(i<=n){
                announcing();
                i++;
            }
        }

};






//
// argc is the number of command-line arguments, i.e. the size of argv
//
// argv is an array of strings, where each string is a command-line argument;
//      argv[0] is the program name that is run, e.g. "./getline_demo"

int main(int argc, char *argv[])
{
    //Create object of Jinglenet Class
    Jinglenet system;

    // Check that the user provided a filename.
   
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;

        return 1; 
    }

    //
    // Read the contents of the file named by argv[1]
    //
    string filename = argv[1];

    //opens the file
    ifstream infile(filename);
    string line;

    //strings to store components of instruction
    
    //What to do
    string command;
    
    //sender
    string username;
    
    //Who the annoucement is for
    string rank;


    //loop through each line of file
    while (getline(infile, line))
    {

    //Sets the command to be from position 0 to the first space in the line
      size_t spacePos = line.find(' ');
      command = line.substr(0, spacePos);
      
      //Params is what is passed as an Annoucement, everything after the command
      string params = line.substr(spacePos + 1);

      //the Sender will be the first word in the annoucement (params)
      //from spacePos+1 to the next space of the original line
      //If command is ANOUNCE the username will be the number to Announce
      spacePos = params.find(' ');
      username = params.substr(0,spacePos);

      //New substring to store remains of line
      string newsub = params.substr(spacePos+1);

      //Rank is the first word after the sender. (First word in newsub)
      spacePos = newsub.find(' ');
      rank = newsub.substr(0,spacePos);
     
      //Proceed with the proper tasks based on the instruction

      //sending an annoucement
      //Create an annucement from the Params created above
      //Send the annoucement in the JingleNet class using the system object created using send function.      
      if(command == "SEND"){
        Announcement announce(params);
        system.send(rank,announce);
      }
      //Pass username though jinglenet System using clear function
      //Removes all instances of username in all queues.
      else if(command == "REMOVE_ALL"){
        system.clear(username);
      }
      //Pass username though jinglenet System using promote function
      //Promotes all instances of username to next highest rank
      else if(command == "PROMOTE_ANNOUNCEMENTS"){
        system.promote(username);
      }
      //Username actually is the number to announce.
      // Passes number through jinglenet system using announce function
      else if(command == "ANNOUNCE"){
        system.announce(username);
      }
    }

} // main
