/*
EECS 348 Programming Assignment 1
This program is a CEO email prioritization program that assigns a priority number to each email sender and filters the emails in the order by which they should be read
The input for this program will be any txt file. For the purpose of this assignment, the input will be Assignment1_Test_File.txt
The output for this program will be the emails 
Collaborator: None
I used chatgpt to assist me in the a part of the maxheap (I specify when) implementation because I am still a freshman and am doing EECS 268 as a corequisite so I am not as familiat with it.
Nischay Rawal
Creation Date: 01/28/2025
*/

#include <iostream>  // This line includes the standard input-output stream library
#include <queue>     // This line includes the queue library for priority queue implementation
#include <vector>    // This line includes the vector library for dynamic arrays
#include <sstream>   // This line includes the sstream library for string stream processing
#include <map>      // This line includes the map library for storing sender priority
#include <fstream>  // This line includes the file stream library for file handling

// This structure represents an email with priority for sorting
struct Email {
    int priority;       // This line declares an integer variable 'priority' for email priority level
    std::string sender; // This line declares a string variable 'sender' for sender category
    std::string subject;// This line declares a string variable 'subject' for email subject
    std::string date;   // This line declares a string variable 'date' for email date
    int timestamp;      // This line declares an integer variable 'timestamp' for arrival order

    // This is a constructor to initialize an Email object
    Email(int p, std::string s, std::string sub, std::string d, int t) 
        : priority(p), sender(s), subject(sub), date(d), timestamp(t) {}
};

// This is a comparison operator for priority queue to order emails
struct CompareEmail {
    bool operator()(const Email& e1, const Email& e2) {
        if (e1.priority == e2.priority) {
            return e1.timestamp < e2.timestamp; // This line ensures newer emails are prioritized
        }
        return e1.priority < e2.priority; // This line ensures higher priority emails are on top
    }
};

int main() {
    std::ifstream inputFile("Assignment5_Test_File.txt"); // Open the test file for reading
    if (!inputFile) {
        std::cerr << "Error: Could not open Assignment5_Test_File.txt" << std::endl;
        return 1; // Exit with error code if file cannot be opened
    }

    std::priority_queue<Email, std::vector<Email>, CompareEmail> emailQueue; // This line declares a priority queue of Email objects
    std::map<std::string, int> priorityMap = { // This map assigns priority values to sender categories
        {"Boss", 5},
        {"Subordinate", 4},
        {"Peer", 3},
        {"ImportantPerson", 2},
        {"OtherPerson", 1}
    };

    int emailCount = 0; // This line initializes a counter for emails
    std::string line;   // This line declares a string variable for reading input lines

    // Read input from the file instead of standard input
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line); // This line creates a string stream from the input line
        std::string command;
        ss >> command; // This line extracts the command (EMAIL, NEXT, READ, COUNT)

        if (command == "EMAIL") {
            std::string sender, subject, date;
            std::getline(ss, sender, ',');
            std::getline(ss, subject, ',');
            std::getline(ss, date);
            sender.erase(0, 1); // This line removes leading space
            
            int priority = priorityMap[sender]; // This line gets priority from the map
            emailQueue.push(Email(priority, sender, subject, date, emailCount++)); // This line adds the email to the queue
        } 
        else if (command == "COUNT") {
            std::cout << "There are " << emailQueue.size() << " emails to read." << std::endl; // This line prints email count
        } 
        else if (command == "NEXT") {
            if (!emailQueue.empty()) {
                Email nextEmail = emailQueue.top(); // This line gets the highest priority email
                std::cout << "\nNext email:" << std::endl;
                std::cout << "Sender: " << nextEmail.sender << std::endl;
                std::cout << "Subject: " << nextEmail.subject << std::endl;
                std::cout << "Date: " << nextEmail.date << std::endl;
            } else {
                std::cout << "No emails available." << std::endl; // This line handles an empty queue
            }
        } 
        else if (command == "READ") {
            if (!emailQueue.empty()) {
                emailQueue.pop(); // This line removes the highest priority email
            } else {
                std::cout << "No emails to read." << std::endl; // This line handles an empty queue
            }
        }
    }

    inputFile.close(); // Close the file when done
    return 0; // This line returns 0 indicating successful program execution
}
