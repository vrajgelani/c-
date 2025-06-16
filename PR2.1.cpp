#include <iostream>
#include <cstring>
using namespace std;

class Train 
{
private:
    int trainNumber;
    char trainName[50];
    char source[50];
    char destination[50];
    char trainTime[10];
    static int trainCount;

public:
    Train() 
	{
        trainNumber = 0;
        strcpy(trainName, "");
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(trainTime, "");
        trainCount++;
    }

    Train(int number, const char* name, const char* src, const char* dest, const char* time) {
        trainNumber = number;
        strcpy(trainName, name);
        strcpy(source, src);
        strcpy(destination, dest);
        strcpy(trainTime, time);
        trainCount++;
    }

    ~Train() 
	{
        trainCount--;
    }

    void inputTrainDetails() 
	{
        cout << "Enter Train Number: ";
        cin >> trainNumber;
        cin.ignore(); 
        cout << "Enter Train Name: ";
        cin.getline(trainName, 50);
        cout << "Enter Source: ";
        cin.getline(source, 50);
        cout << "Enter Destination: ";
        cin.getline(destination, 50);
        cout << "Enter Train Time: ";
        cin.getline(trainTime, 10);
    }

    void displayTrainDetails() const 
	{
        cout << "Train Number: " << trainNumber << endl;
        cout << "Train Name: " << trainName << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Train Time: " << trainTime << endl;
    }

    int getTrainNumber() const 
	{
        return trainNumber;
    }

    static int getTrainCount() 
	{
        return trainCount;
    }
};

int Train::trainCount = 0;

class RailwaySystem 
{
private:
    Train trains[100];
    int totalTrains;

public:
    RailwaySystem() 
	{
        totalTrains = 0;
    }

    void addTrain() 
	{
        if (totalTrains < 100) 
		{
            trains[totalTrains].inputTrainDetails();
            totalTrains++;
        } else 
		{
            cout << "Train storage is full!" << endl;
        }
    }

    void displayAllTrains() const 
	{
        if (totalTrains == 0) 
		{
            cout << "No train records found." << endl;
            return;
        }
        for (int i = 0; i < totalTrains; ++i) 
		{
            cout << "\nTrain " << i + 1 << " details:" << endl;
            trains[i].displayTrainDetails();
        }
    }

    void searchTrainByNumber(int number) const 
	{
        bool found = false;
        for (int i = 0; i < totalTrains; ++i) 
		{
            if (trains[i].getTrainNumber() == number) 
			{
                cout << "\nTrain Found:\n";
                trains[i].displayTrainDetails();
                found = true;
                break;
            }
        }
        if (!found) 
		{
            cout << "Train with number " << number << " not found!" << endl;
        }
    }
};
int main() 
{
    RailwaySystem rs;
    int choice;

    cout << "Enter details for 3 initial train records:\n";
    for (int i = 0; i < 3; ++i)
	{
        cout << "--- Train " << (i + 1) << " ---" << endl;
        rs.addTrain();
    }

    do 
	{
        cout << "\n--- Railway Reservation System Menu ---\n";
        cout << "1. Add New Train Record\n";
        cout << "2. Display All Train Records\n";
        cout << "3. Search Train by Number\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
        case 1:
            rs.addTrain();
            break;
        case 2:
            rs.displayAllTrains();
            break;
        case 3: 
		{
            int searchNum;
            cout << "Enter Train Number to search: ";
            cin >> searchNum;
            rs.searchTrainByNumber(searchNum);
            break;
        }
        case 4:
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
/*
output:Enter details for 3 initial train records:
--- Train 1 ---
Enter Train Number: 101
Enter Train Name: Okha Express
Enter Source: Surat
Enter Destination: Mumbai
Enter Train Time: 10 AM

--- Railway Reservation System Menu ---
1. Add New Train Record
2. Display All Train Records
3. Search Train by Number
4. Exit
Enter your choice: 2
Train 1 details:
Train Number: 101
Train Name: Okha Express
Source: Surat
Destination: Mumbai
Train Time: 10 AM

*/