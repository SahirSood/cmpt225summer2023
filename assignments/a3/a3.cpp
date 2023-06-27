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
        Announcement announcing;
        Node* next;

        Node(const Announcement &a, Node *n) : announcing(a), next(n) {} 
        
    };
    Node*begin,*rear;
    int sz;

    public:

        Queue() : begin(nullptr), rear(nullptr), sz(0) {}

        
        ~Queue(){
            Node* cur = begin;
            while (cur != nullptr) {
                Node* temp = cur;
                cur = cur->next;
                delete temp;
            }
}

        int size()const{
            return sz;
        }


        void enqueue(const Announcement &annouce){
            Node* temp = new Node(annouce,nullptr);
            cout<<temp->announcing.to_string()<<endl;
            if (rear==NULL){
                begin = rear = temp;
                sz++;   
                return;

            }
            rear->next = temp;
            rear = temp;
            sz++;
        }

        const Announcement &front()const{
            return begin->announcing;
        }
        void dequeue(){
            if(sz == 0){
                throw runtime_error("dequeue: queue is empty");
            }
            Node* temp = begin;
            begin = begin->next;
            
            if(begin == nullptr){
                rear = nullptr;
            }
            sz--;
            delete temp;
        }
        
};


class Jinglenet
{
    private:
        
        Queue santa;
        Queue reindeer;
        Queue elf1;
        Queue elf2;
        Queue snowman;

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

        Jinglenet(){}
        ~Jinglenet(){}

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
        void clear(string name){
            Queue* QueuePointer = nullptr;
            Queue temp;
            for(int i =1;i<=5;i++){
                QueuePointer = queueswitch(i);
                while(QueuePointer->size()!=0){
                    cout<<QueuePointer->size()<<endl;
                    string peekName = QueuePointer->front().get_sender_name();
                    Announcement peekAnnounce = QueuePointer->front();
                    if(peekName == name){
                        QueuePointer->dequeue();
                    }
                    else{
                        temp.enqueue(peekAnnounce);
                        QueuePointer->dequeue();
                    }
                    cout<<QueuePointer->size()<<endl;
                }
                while(temp.size()!=0){
                    Announcement peekAnnounce = temp.front();
                    QueuePointer->enqueue(peekAnnounce);
                    temp.dequeue();
                }
            }
        }

        void promote(string name){
            Queue temp;
            Queue* QueuePointer =nullptr;
            Queue* PromotionPointer =nullptr;
            for(int i=1;i<=4;i++){
                QueuePointer = queueswitch(i);
                PromotionPointer = queueswitch(i+1);
                while(QueuePointer->size()!=0){
                    string peekName = QueuePointer->front().get_sender_name();
                    Announcement peekAnnounce = QueuePointer->front();
                    if(peekName == name){
                        PromotionPointer->enqueue(peekAnnounce);
                        QueuePointer->dequeue();
                    }
                    else{
                        temp.enqueue(peekAnnounce);
                        QueuePointer->dequeue();
                    }
                }
                while(temp.size()!=0){
                    Announcement peekAnnounce = temp.front();
                    QueuePointer->enqueue(peekAnnounce);
                    temp.dequeue();
                }
            }
        }
        void announce(string number){
            int n = stoi(number);
            int i=0;
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
    Jinglenet system;

    // Check that the user provided a filename.
   
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;

        return 1; 
    }

    //
    // Read the contents of the file named by argv[1], and print each line.
    //
    

    string filename = argv[1];


    ifstream infile(filename);
    string line;


    string command;
    string username;
    string rank;



    while (getline(infile, line))
    {

      size_t spacePos = line.find(' ');
      command = line.substr(0, spacePos);
      string params = line.substr(spacePos + 1);

      spacePos = params.find(' ');
      username = params.substr(0,spacePos);
      string newsub = params.substr(spacePos+1);
      spacePos = newsub.find(' ');
      rank = newsub.substr(0,spacePos);
     

      if(command == "SEND"){
        Announcement announce(params);
        system.send(rank,announce);
      }
      else if(command == "REMOVE_ALL"){
        system.clear(username);
      }
      else if(command == "PROMOTE_ANNOUNCEMENTS"){
        system.promote(username);
      }
      else if(command == "ANNOUNCE"){
        system.announce(username);
        cout<<"announce"<<endl;
      }
    }

} // main
