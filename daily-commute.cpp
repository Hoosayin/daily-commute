#include "LinkedList.h"

#include <iostream>
#include <fstream>
#include <conio.h>

int main()
{
	int* trainStations{};
	int* busStations{};
	int* scooterStations{};
	int* walkingStations{};

	int numberOfTrainStations{};
	int numberOfBusStations{};
	int numberOfScooterStations{};
	int numberOfWalkingStations{};

	std::string filename{};
	std::string word{};
	std::ifstream inputFile{};

	Node* bestPath{};

	LinkedList linkedList{};
	LinkedList duplicate{};

	std::cout << "Enter a layered list input file => ";
	std::cin >> filename;

	std::cout << std::endl;

	// Open input.txt file.
	inputFile.open("./" + filename, std::ios::in);

	// Return if file failed to open.
	if (!inputFile.is_open())
	{
		std::cout << "Cannot open " << filename << "." << std::endl;
		return -1;
	}

	// Read number of train stations.
	if (!(inputFile >> word))
	{
		std::cout << "Failed to read number of train stations." << std::endl;
		return -1;
	}

	// Create array of train stations.
	numberOfTrainStations = atoi(word.c_str());
	trainStations = new int[numberOfTrainStations];

	// Read each train station from the file.
	for (int i = 0; i < numberOfTrainStations; ++i)
	{
		if (!(inputFile >> word))
		{
			std::cout << "Failed to read train station." << std::endl;
			return -1;
		}

		trainStations[i] = atoi(word.c_str());
	}

	// Read number of bus stations.
	if (!(inputFile >> word))
	{
		std::cout << "Failed to read number of bus stations." << std::endl;
		return -1;
	}

	// Create array of bus stations.
	numberOfBusStations = atoi(word.c_str());
	busStations = new int[numberOfBusStations];

	// Read each bus station from the file.
	for (int i = 0; i < numberOfBusStations; ++i)
	{
		if (!(inputFile >> word))
		{
			std::cout << "Failed to read bus station." << std::endl;
			return -1;
		}

		busStations[i] = atoi(word.c_str());
	}

	// Read number of walking stations.
	if (!(inputFile >> word))
	{
		std::cout << "Failed to read number of walking stations." << std::endl;
		return -1;
	}

	// Create array of walking stations.
	numberOfWalkingStations = atoi(word.c_str());
	walkingStations = new int[numberOfWalkingStations];

	// Read each walking station from the file.
	for (int i = 0; i < numberOfWalkingStations; ++i)
	{
		if (!(inputFile >> word))
		{
			std::cout << "Failed to read walking station." << std::endl;
			return -1;
		}

		walkingStations[i] = atoi(word.c_str());
	}

	// Close input.txt file.
	inputFile.close();

	// Make Linked List.
	linkedList.MakeList(
		trainStations, 
		busStations, 
		walkingStations, 
		numberOfWalkingStations);

	// Delete Arrays.
	delete[] trainStations;
	trainStations = nullptr;

	delete[] busStations;
	busStations = nullptr;

	delete[] walkingStations;
	walkingStations = nullptr;
	
	unsigned short choice{};
	char testAgain{'N'};

	do
	{
		system("CLS");

		std::cout << "What method would you like to test?" << std::endl;
		std::cout << "1. MakeList() (Already Created)" << std::endl;
		std::cout << "2. RemoveTrainStation()" << std::endl;
		std::cout << "3. AddBusStop()" << std::endl;
		std::cout << "4. BestPath()" << std::endl;
		std::cout << "5. Duplicate()" << std::endl;
		std::cout << "6. AddScooter()" << std::endl;

		std::cout << "Enter a number => ";
		std::cin >> choice;

		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			std::cout << "List is already created." << std::endl;
			break;
		case 2:
			std::cout << "Original List:" << std::endl;
			linkedList.Display();

			std::cout << "Enter a station to remove => ";
			std::cin >> choice;
			std::cout << std::endl;

			linkedList.RemoveTrainStation(choice);

			std::cout << "Final List:" << std::endl;
			linkedList.Display();

			break;
		case 3:
			std::cout << "Original List:" << std::endl;
			linkedList.Display();

			std::cout << "Enter a bus stop to add => ";
			std::cin >> choice;
			std::cout << std::endl;

			linkedList.AddBusStation(choice);

			std::cout << "Final List:" << std::endl;
			linkedList.Display();

			break;
		case 4:
			std::cout << "Layered Linked List:" << std::endl;
			linkedList.Display();

			std::cout << "Enter a destination => ";
			std::cin >> choice;
			std::cout << std::endl;

			std::cout << "Best Path:" << std::endl;
			bestPath = linkedList.BestPath(choice);

			break;
		case 5:
			std::cout << "Original List:" << std::endl;
			linkedList.Display();

			// Call Copy Constructor that recursively deep copies all node in "duplicate".
			duplicate = linkedList;

			std::cout << "Duplicate:" << std::endl;
			duplicate.Display();

			break;
		case 6:
			std::cout << "Original List:" << std::endl;
			linkedList.Display();

			std::cout << "Enter scooter layer input file => ";
			std::cin >> filename;
			std::cout << std::endl;

			// Open input.txt file.
			inputFile.open("./" + filename, std::ios::in);

			// Return if file failed to open.
			if (!inputFile.is_open())
			{
				std::cout << "Cannot open " << filename << "." << std::endl;
				break;
			}

			// Read number of scooter stations.
			if (!(inputFile >> word))
			{
				std::cout << "Failed to read number of scooter stations." << std::endl;
				break;
			}

			// Create array of scooter stations.
			numberOfScooterStations = atoi(word.c_str());
			scooterStations = new int[numberOfScooterStations];

			// Read each scooter station from the file.
			for (int i = 0; i < numberOfScooterStations; ++i)
			{
				if (!(inputFile >> word))
				{
					std::cout << "Failed to read scooter station." << std::endl;
					break;
				}

				scooterStations[i] = atoi(word.c_str());
			}

			inputFile.close();

			linkedList.AddScooter(scooterStations, numberOfScooterStations);

			// Delete array of scooter stations.
			delete[] scooterStations;
			scooterStations = nullptr;

			std::cout << "Final List:" << std::endl;
			linkedList.Display();
			break;
		default:
			break;
		}

		std::cout << "Do you want to test again => ";
		std::cin >> testAgain;
		std::cout << std::endl;

	} while (testAgain == 'Y' || testAgain == 'y');
}
