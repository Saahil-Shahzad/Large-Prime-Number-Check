/*
    # Large Prime Number    #
    # Checker in c++        #
    -------------------------
    # By: Saahil Shahzad    #
    #     469370            #
    -------------------------
    # 11/4/2024             # 

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>

// defining a prime number component as a node
struct primeComponentNode
{
    int digits; // to store groups of nine digits as prime number component

    primeComponentNode* next;  // will point to the next prime component node

    primeComponentNode(int digits) : digits(-1), next(nullptr) {}  // constructor (digits(-1) indicates no digits)
};

// singly linked list to store large prime number 
class PrimeNumberList
{
    int numOfComponents; // size of the prime number list
    primeComponentNode* head;  // point to the head of the list

    public:
        PrimeNumberList() : numOfComponents(0), head(nullptr) {}    // constructor

        ~PrimeNumberList()  // destructor
        {
            primeComponentNode* temp = head;

            while (temp != nullptr) // iterating through the list
            {
                primeComponentNode* next = temp->next;    // storing the next node
                delete temp;    // deallocating the current node
                temp = next;    // moving to the next node
            }
        }

        // inserts a prime component node at the end
        void insertPrimeComponentAtEnd(int primeComponent)
        {
            numOfComponents++;   // incrementing the component counter

            primeComponentNode* newNode = new primeComponentNode(primeComponent);

            if (isEmpty())  // if list is empty, make new node the head  
            {
                head = newNode;
                newNode = nullptr;
            }
            else    // if list is not empty, insert at the end
            {
                primeComponentNode* temp = head;

                while (temp->next != nullptr)   // iterating to the end
                {
                    temp = temp->next;
                }

                temp->next = newNode;   // making the end node point to the new node
            }
        }

        // to remove a prime component node from the list
        void deletePrimeComponent(primeComponentNode* primeComponentToDelete)
        {
            numOfComponents--;   // decrementing the component counter

            if (head == primeComponentToDelete) // if head is the node to be deleted, make next node in the list the head then delete the node
            {
                head = primeComponentToDelete->next;
                delete primeComponentToDelete;
            }
            else    // if head is not the node to be deleted, bypass and delete the node
            {
                primeComponentNode* temp = head;

                while (temp->next != primeComponentToDelete)    // iterating to the node before the node to be deleted
                {
                    temp = temp->next;
                }

                temp->next = primeComponentToDelete->next;  // bypassing the node to be deleted

                delete primeComponentToDelete;  // deallocating the node to be deleted
            }
        }

        // to check whether the list is empty
        bool isEmpty()
        {
            if (!head)  // if list is empty return true
            {
                return true;
            }

            return false;   // else return false
        }

        // to display the prime number list
        void display()
        {
            primeComponentNode* temp = head;

            std::cout << "Input (1024-bit number): \"";
            while (temp != nullptr) // iterating through the list
            {
                std::cout << temp->digits; // displaying the prime component
                temp = temp->next;  // moving to the next node
            }
            std::cout << "\"\n";

            std::cout << "Smaller primes: [2, 3, 5, 7, 11,...]\n";

            std::cout << std::endl; // new line
        }

        // to generate a random 1024-bit (309 digits) number
        std::string generateRandom309DigitsNumber()
        {
            std::string random309DigitsNumber = "";    // to store the random number

            for (int i = 0; i < 309; i++)   // generating 309 digits
            {
                random309DigitsNumber += std::to_string(rand() % 10);    // adding a random digit to the number
            }

            return random309DigitsNumber;   // returning the random number
        }

        // to store the prime number into the list
        void storeStringIntoPrimeNumberList(std::string primeNumber)
        {
            int digitCounter = 0;   // to count the digits getting stored into the prime component
            std::string primeComponent = "";    // to store the digits as a prime component

            for (char c : primeNumber)
            {
                digitCounter++; // incrementing the digit counter

                primeComponent += c;    // adding the digit to the prime component

                if (digitCounter == 4)  // if 9 digits have been stored in the component, add the component to the list and reset the counter
                {
                    insertPrimeComponentAtEnd(std::stoi(primeComponent));    // adding the prime component to the list

                    digitCounter = 0;    // resetting the digit counter
                }
            }
        }

        std::string listToString(PrimeNumberList list)
        {
            std::string primeNumber = "";    // to store the prime number

            primeComponentNode* temp = list.head;

            while (temp != nullptr) // iterating through the entire list
            {
                primeNumber += std::to_string(temp->digits); // adding the prime component to the prime number
                temp = temp->next;  // moving to the next node
            }

            return primeNumber; // returning the prime number
        }

        // to check the primality of the number
        bool validatePrimeNumber(PrimeNumberList primeNumberList)
        {
            if (isEmpty())  // if list is empty, inform and return
            {
                std::cout << "Nothing to validate.\n";
                return false;   // "nothing" is not a prime number
            }

            // !!! this implementation is not working, it terminates with an error of "std::out_of_range" because the number is too large to fit in primitive datatypes

            // std::string primeNumber = listToString(primeNumberList);    // converting the list to a string

            // for (int i = 2; i <= std::sqrt(std::stoi(primeNumber)); i++)
            // {
            //     if (std::stoi(primeNumber) % i == 0)   // if the number is divisible by any number other than 1 and itself, it is not prime
            //     {
            //         return false;
            //     }
            // }

            primeComponentNode* temp = head;

            // to be used in the loops below
            bool lastNodePrimality;
            bool secondLastNodePrimality;


            while(temp->next->next != nullptr)    // making temp point to the second last node
            {
                temp = temp->next;
            }

            for (int i = 2; i <= std::sqrt(temp->digits); i++)
            {
                if ((temp->digits) % i == 0)   // if the number is divisible by any number other than 1 and itself, it is not prime
                {
                    secondLastNodePrimality = false;
                }
            }

            while(temp->next != nullptr)    // making temp point to the last node
            {
                temp = temp->next;
            }

            for (int i = 2; i <= std::sqrt(temp->digits); i++)
            {
                if ((temp->digits) % i == 0)   // if the number is divisible by any number other than 1 and itself, it is not prime
                {
                    lastNodePrimality = true;
                }
            }

            bool result = lastNodePrimality && secondLastNodePrimality;     // to determine probabilistically   

            return result;
        }
};


int main()
{   
    PrimeNumberList primeNumberList;    // creating the prime number list

    primeNumberList.storeStringIntoPrimeNumberList(primeNumberList.generateRandom309DigitsNumber());    // reading and storing the prime number

    primeNumberList.display();    // displaying the prime number

    std::cout << (primeNumberList.validatePrimeNumber(primeNumberList) ? "True\n" : "False\n");    // validating the prime number

    return 0;
}