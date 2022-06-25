#include "LinkedList.h"
#include <iostream>
#include <string>

LinkedList::LinkedList()
{
}

LinkedList::LinkedList(const LinkedList& other)
{
	m_isScookerLayerAdded = other.m_isScookerLayerAdded;

	// Recursively create a deep copy of other linked list.
	m_trainZero = DeepCopy(other.m_trainZero);
}

LinkedList::~LinkedList()
{
	if (m_trainZero == nullptr)
		return;

	// Recursively delete entire layered linked list.
	Node* trainStation = m_trainZero;
	Node* busStation = trainStation->GetDown();
	Node* scooterStation{ nullptr };
	Node* walkingStation{ nullptr };

	// Check if scooter layer is added.
	if (m_isScookerLayerAdded == true)
	{
		scooterStation = busStation->GetDown();
		walkingStation = scooterStation->GetDown();
	}
	else
	{
		walkingStation = busStation->GetDown();
	}

	// Delete walking stations.
	DeleteStation(walkingStation);

	// Delete scooter stations.
	DeleteStation(scooterStation);

	// Delete bus stations.
	DeleteStation(busStation);

	// Delete train stations.
	DeleteStation(trainStation);

	// Clear flags.
	m_isScookerLayerAdded = false;

	// Clear station pointers.
	m_trainZero = nullptr;
}

void LinkedList::DeleteStation(Node* station)
{
	// Return if station is already null.
	if (station == nullptr)
		return;

	// Recursively delete its next stations.
	DeleteStation(station->GetNext());

	// Delete station.
	delete station;
	station = nullptr;
}

void LinkedList::operator=(const LinkedList& other)
{
	m_isScookerLayerAdded = other.m_isScookerLayerAdded;

	// Recursively create a deep copy of other linked list.
	m_trainZero = DeepCopy(other.m_trainZero);
}

void LinkedList::SetTrainZero()
{
	// Check if First Train Station is already created.
	if (m_trainZero != nullptr)
	{
		std::cout << "First train station is already created." << std::endl;
		return;
	}

	// Create First Walking Station.
	Node* walkingZero = new Node();
	walkingZero->SetLocation(0);

	// Create First Bus Station.
	Node* busZero = new Node();
	busZero->SetDown(walkingZero);
	busZero->SetLocation(0);

	// Create First Train Station.
	m_trainZero = new Node();
	m_trainZero->SetDown(busZero);
	m_trainZero->SetLocation(0);
}

void LinkedList::CreateBestPathStationString(Node* station, std::string& stationString, Node*& lastStation)
{
	int stationStep = 0; // Station step starting from 0.
	bool isFirstStationFound{ false }; // Used for padding string.

	// Iterate each station.
	while (station)
	{
		// Check if station is the same as station step.
		if (station->GetLocation() == stationStep)
		{
			// Concatenate station string.
			stationString += std::to_string(station->GetLocation());

			// Check if this station is the last station of current layer.
			if (station->GetNext() == nullptr)
				lastStation = station;

			// Go to next station.
			station = station->GetNext();

			// Concatenate ">>" if this is not the last station.
			if (station != nullptr)
				stationString += ">>";

			// Update flag for first occurance of station is concatenated in station string.
			isFirstStationFound = true;
		}
		// Otherwise add padding in the string.
		else
		{
			// Calculate number of padded values to be added.
			int padding = std::to_string(stationStep).length() + 2;

			// Add padding.
			for (int i = 0; i < padding; ++i)
				stationString += isFirstStationFound ? ">" : " ";
		}

		// Increment station step.
		++stationStep;
	}
}

Node* LinkedList::GetBestPathStation(Node* station, int destination)
{
	// Initialize a new best path station.
	Node* newStation = new Node();

	// Return if station is null or location is greater than destination.
	if (station == nullptr ||
		station->GetLocation() > destination)
	{
		newStation = nullptr;
	}
	// Else if location is the same as destination, no need to go any further.
	else if (station->GetLocation() == destination)
	{
		newStation->SetLocation(station->GetLocation());
		
		// Move to down layer if it exists. 
		if (station->GetDown() != nullptr)
		{
			newStation->SetDown(GetBestPathStation(station->GetDown(), destination));
		}
	}
	// Else add last location to best path, and check if we can take next station or move to down layer.
	else
	{
		// Add last location to path.
		newStation->SetLocation(station->GetLocation());

		// Get next best path station.
		Node* nextStation = GetBestPathStation(station->GetNext(), destination);

		// If next best path station is found, connect it with new station.
		if (nextStation != nullptr)
		{
			newStation->SetNext(nextStation);
		}
		// Otherwise, search in the down layer.
		else
		{
			Node* downStation = GetBestPathStation(station->GetDown(), destination);
			newStation->SetDown(downStation);
		}
	}

	return newStation;
}

void LinkedList::DisplayBestPath(Node* bestPath)
{
	// Return if best path is null.
	if (bestPath == nullptr)
		return;

	std::cout << std::endl;

	std::string trainStationsString{ "" };
	std::string rowAboveBusStations{ "" };
	std::string busStationsString{ "" };
	std::string rowAboveScooterStations{ "" };
	std::string scooterStationsString{ "" };
	std::string rowAboveWalkingStations{ "" };
	std::string walkingStationsString{ "" };

	Node* trainStation = bestPath;
	Node* lastTrainStation{ nullptr };

	// Create string for train stations.
	CreateBestPathStationString(
		trainStation, 
		trainStationsString, 
		lastTrainStation);

	while (rowAboveBusStations.length() != trainStationsString.length() - 1)
		rowAboveBusStations += " ";

	rowAboveBusStations += "v";

	Node* busStation = lastTrainStation->GetDown();
	Node* lastBusStation{ nullptr };

	// Create string for bus stations.
	CreateBestPathStationString(
		busStation,
		busStationsString,
		lastBusStation);

	if (m_isScookerLayerAdded == true)
	{
		while (rowAboveScooterStations.length() != busStationsString.length() - 1)
			rowAboveScooterStations += " ";

		rowAboveScooterStations += "v";

		Node* scooterStation = lastBusStation->GetDown();
		Node* lastScooterStation{ nullptr };

		// Create string for scooter stations.
		CreateBestPathStationString(
			scooterStation,
			scooterStationsString,
			lastScooterStation);

		while (rowAboveWalkingStations.length() != scooterStationsString.length() - 1)
			rowAboveWalkingStations += " ";

		rowAboveWalkingStations += "v";

		Node* walkingStation = lastScooterStation->GetDown();
		Node* lastWakingStation{ nullptr };

		// Create string for walking stations.
		CreateBestPathStationString(
			walkingStation,
			walkingStationsString,
			lastWakingStation);
	}
	else
	{
		while (rowAboveWalkingStations.length() != busStationsString.length() - 1)
			rowAboveWalkingStations += " ";

		rowAboveWalkingStations += "v";

		Node* walkingStation = lastBusStation->GetDown();
		Node* lastWakingStation{ nullptr };

		// Create string for walking stations.
		CreateBestPathStationString(
			walkingStation,
			walkingStationsString,
			lastWakingStation);
	}

	// Display best path on console.
	std::cout << trainStationsString << std::endl;
	std::cout << rowAboveBusStations << std::endl;
	std::cout << busStationsString << std::endl;

	if (m_isScookerLayerAdded == true)
	{
		std::cout << rowAboveScooterStations << std::endl;
		std::cout << scooterStationsString << std::endl;
	}

	std::cout << rowAboveWalkingStations << std::endl;
	std::cout << walkingStationsString << std::endl;

	std::cout << std::endl;
}

Node* LinkedList::DeepCopy(Node* other)
{
	// Return of other station is null.
	if (other == nullptr)
		return nullptr;

	// Create a new station.
	Node* newStation = new Node();
	newStation->SetLocation(other->GetLocation()); // Set Location.

	// Recursively get deep copy of next station.
	newStation->SetNext(DeepCopy(other->GetNext()));

	// Recursively get deep copy of down station.
	newStation->SetDown(DeepCopy(other->GetDown()));

	// Return new station.
	return newStation;
}

bool LinkedList::IsDistantThanLastWalkingStation(int location)
{
	// Get first walking station.
	Node* walkingStation = (m_isScookerLayerAdded == true) ?
		m_trainZero->GetDown()->GetDown()->GetDown() :
		m_trainZero->GetDown()->GetDown();

	// Iterate all walking stations.
	while (walkingStation)
	{
		// Check if last walking station is greater than location.
		if (walkingStation->GetNext() == nullptr)
		{
			if (location > walkingStation->GetLocation())
			{
				std::cout << "Location " << location
					<< " is greater than last walking station, i.e., "
					<< walkingStation->GetLocation() << "." << std::endl;

				return true;
			}
		}

		// Go to next walking station.
		walkingStation = walkingStation->GetNext();
	}

	return false;
}

void LinkedList::MakeList(
	int* trainStations, 
	int* busStations, 
	int* walkingStations,
	int numberOfWalkingStations)
{
	// Initialize Train Zero.
	SetTrainZero();

	Node* trainStation = m_trainZero;
	Node* busStation = trainStation->GetDown();
	Node* walkingStation = busStation->GetDown();

	// Start by adding walking stations.
	for (int i = 0; i < numberOfWalkingStations; ++i)
	{
		// Create a new node for walking station.
		Node* newWalkingStation = new Node();
		newWalkingStation->SetLocation(walkingStations[i]);

		// Update last Walking Station.
		walkingStation->SetNext(newWalkingStation);
		walkingStation = newWalkingStation;

		// Check if bus station also exists on this walking station.
		if (*busStations == walkingStations[i])
		{
			// Create a new node for bus station.
			Node* newBusStation = new Node();
			newBusStation->SetDown(newWalkingStation);
			newBusStation->SetLocation(*busStations);

			// Update last Bus Station.
			busStation->SetNext(newBusStation);
			busStation = newBusStation;

			// Check if train station also exists on this bus station.
			if (*trainStations == *busStations)
			{
				// Create a new node for train station.
				Node* newTrainStation = new Node();
				newTrainStation->SetDown(busStation);
				newTrainStation->SetLocation(*trainStations);

				trainStation->SetNext(newTrainStation);
				trainStation = newTrainStation;

				// Increment array of train stations.
				++trainStations;
			}

			// Increment array of bus stations.
			++busStations;
		}
	}
}

void LinkedList::RemoveTrainStation(int location)
{
	// Return if location to be deleted is 0.
	if (location == 0)
	{
		std::cout << "Cannot remove train station 0." << std::endl;
		return;
	}

	Node* trainStation = m_trainZero;
	Node* previousTrainStation = trainStation;

	bool isTrainStationDeleted{ false };

	// Iterate each train station.
	while (trainStation)
	{
		// Check if train station has the location to be deleted.
		if (trainStation->GetLocation() == location)
		{
			// Update adjacent train stations.
			previousTrainStation->SetNext(trainStation->GetNext());

			// Delete train station.
			delete trainStation;
			trainStation = nullptr;

			// Update flag.
			isTrainStationDeleted = true;

			// Break the loop.
			break;
		}

		previousTrainStation = trainStation;

		// Go to next train station.
		trainStation = trainStation->GetNext();
	}

	if (isTrainStationDeleted == true)
	{
		std::cout << "Train station " << location << " removed." << std::endl;
	}
	else
	{
		std::cout << "Train station " << location << " not found." << std::endl;
	}
}

void LinkedList::AddScooter(int* scooterStations, int numberOfScooterStations)
{
	Node* busStation = m_trainZero->GetDown();
	Node* walkingStation = busStation->GetDown();

	// Add Scooter Zero.
	Node* scooterZero = new Node();
	scooterZero->SetLocation(0);
	scooterZero->SetDown(walkingStation);

	Node* previousScooterStation = scooterZero;

	// Update Bus Zero.
	busStation->SetDown(scooterZero);

	// Go to next walking and bus station.
	walkingStation = walkingStation->GetNext();
	busStation = busStation->GetNext();

	// Iterate each walking station.
	while (walkingStation)
	{
		// Check if scooter station exists on this walking station.
		if (*scooterStations == walkingStation->GetLocation())
		{
			// Add new scooter station.
			Node* newScooterStation = new Node();
			newScooterStation->SetLocation(*scooterStations);
			newScooterStation->SetDown(walkingStation);

			// Update last scooter station.
			previousScooterStation->SetNext(newScooterStation);
			previousScooterStation = newScooterStation;

			// Check if bus station exists on this scooter station.
			if (busStation != nullptr &&
				busStation->GetLocation() == newScooterStation->GetLocation())
			{
				// Update bus station.
				busStation->SetDown(newScooterStation);

				// Go to next bus station.
				busStation = busStation->GetNext();
			}

			// Increment scooter stations.
			++scooterStations;
		}

		// Go to next walking station.
		walkingStation = walkingStation->GetNext();
	}

	m_isScookerLayerAdded = true;
}

void LinkedList::AddBusStation(int location)
{
	// Check if location to be added is the first bus location.
	if (location == 0)
	{
		std::cout << "Bus station 0 already exists." << std::endl;
		return;
	}

	// Return if location is distant from last walking station.
	if (IsDistantThanLastWalkingStation(location) == true)
		return;

	Node* busStation = m_trainZero->GetDown();
	Node* previousBusStation = busStation;

	bool isBusStationFound{ false };

	// Iterate each bus station.
	while (busStation)
	{
		// Check if bus station already has the location to be added.
		if (busStation->GetLocation() == location)
		{
			// Update flag.
			isBusStationFound = true;

			// Break the loop.
			break;
		}
		// Else store the largest existing location less than the location to be added.
		else if (busStation->GetLocation() < location)
		{
			previousBusStation = busStation;
		}

		// Go to next bus station.
		busStation = busStation->GetNext();
	}

	// Add Bus station if it does not exist.
	if (isBusStationFound == false)
	{
		// Create a new node.
		Node* newBusStation = new Node();
		newBusStation->SetLocation(location);

		if (previousBusStation != nullptr)
		{
			newBusStation->SetNext(previousBusStation->GetNext());
		}

		// Connect new bus station with corresponding walknig station.
		Node* walkingStation = m_trainZero->GetDown()->GetDown();

		while (walkingStation)
		{
			// Check if walking station is the same as new bus station.
			if (walkingStation->GetLocation() == location)
			{
				// Connect new bus station with walking station and break the loop.
				newBusStation->SetDown(walkingStation);
				break;
			}

			// Go to next walking station.
			walkingStation = walkingStation->GetNext();
		}

		// Update previous bus station.
		previousBusStation->SetNext(newBusStation);

		std::cout << "Bus station " << location << " added." << std::endl;
	}
	else
	{
		std::cout << "Bus station " << location << " already exists." << std::endl;
	}
}

Node* LinkedList::BestPath(int destination)
{
	// Check if destination is O.
	if (destination == 0)
	{
		std::cout << "You are already at station 0." << std::endl;
		return nullptr;
	}

	// Return if destination is distant than last walking station.
	if (IsDistantThanLastWalkingStation(destination))
		return nullptr;

	// Recursively create best path.
	Node* bestPath = GetBestPathStation(m_trainZero, destination);

	// Display best path.
	DisplayBestPath(bestPath);

	return bestPath;
}

void LinkedList::Display()
{
	std::cout << std::endl;

	Node* trainStation = m_trainZero;
	Node* busStation = trainStation->GetDown();
	Node* scooterStation{ nullptr };
	Node* walkingStation{ nullptr };

	// Check if scooter layer is added.
	if (m_isScookerLayerAdded == true)
	{
		scooterStation = busStation->GetDown();
		walkingStation = scooterStation->GetDown();
	}
	else
	{
		walkingStation = busStation->GetDown();
	}

	std::string trainStationsString{""}; 
	std::string rowAboveBusStations{""};
	std::string busStationsString{""};
	std::string rowAboveScooterStations{""};
	std::string scooterStationsString{""};
	std::string rowAboveWalkingStations{""};
	std::string walkingStationsString{""};

	while (walkingStation)
	{
		// Concatenate arrow head.
		if (walkingStation->GetLocation() != 0)
		{
			walkingStationsString += ">";
			rowAboveWalkingStations += " ";
		}

		// Concatenate walking station.
		walkingStationsString += std::to_string(walkingStation->GetLocation());

		if (walkingStation->GetLocation() == 15)
		{
			int x = 0;
		}

		// Concatenate hyphen.
		if (walkingStation->GetNext() != nullptr)
		{
			walkingStationsString += "-";
		}

		// Check if scooter layer is added.
		if (m_isScookerLayerAdded == true)
		{
			// Check if scooter station exists on this walking station.
			if (scooterStation != nullptr &&
				scooterStation->GetLocation() == walkingStation->GetLocation())
			{
				// Concatenate arrow head.
				if (scooterStation->GetLocation() != 0)
				{
					scooterStationsString += ">";
					rowAboveScooterStations += " ";
				}

				// Concatenate scooter station.
				scooterStationsString += std::to_string(scooterStation->GetLocation());

				// Concatenate hyphen.
				if (scooterStation->GetNext() != nullptr)
				{
					scooterStationsString += "-";
				}

				// Check if bus station exists on this scooter station.
				if (busStation != nullptr &&
					busStation->GetLocation() == scooterStation->GetLocation())
				{
					// Concatenate arrow head.
					if (busStation->GetLocation() != 0)
					{
						busStationsString += ">";
						rowAboveBusStations += " ";
					}

					// Concatenate bus station.
					busStationsString += std::to_string(busStation->GetLocation());

					// Concatenate hypen.
					if (busStation->GetNext() != nullptr)
					{
						busStationsString += "-";
					}

					// Check if train station also exists on this bus station.
					if (trainStation != nullptr &&
						trainStation->GetLocation() == busStation->GetLocation())
					{
						// Concatenate arrow head.
						if (trainStation->GetLocation() != 0)
						{
							trainStationsString += ">";
						}

						// Concatenate train station.
						trainStationsString += std::to_string(trainStation->GetLocation());

						// Concatenate hyphen.
						if (trainStation->GetNext() != nullptr)
						{
							trainStationsString += "-";
						}

						// Concatenate vertical bar.
						rowAboveBusStations += "|";

						// Go to next train station.
						trainStation = trainStation->GetNext();
					}

					// Concatenate vertical bar.
					rowAboveScooterStations += "|";

					// Go to next bus station.
					busStation = busStation->GetNext();
				}

				// Concatenate vertical bar.
				rowAboveWalkingStations += "|";

				// Go to next scooter station.
				scooterStation = scooterStation->GetNext();
			}
		}
		else
		{
			// Check if bus station exists on this walking station.
			if (busStation != nullptr &&
				busStation->GetLocation() == walkingStation->GetLocation())
			{
				// Concatenate arrow head.
				if (busStation->GetLocation() != 0)
				{
					busStationsString += ">";
					rowAboveBusStations += " ";
				}

				// Concatenate bus station.
				busStationsString += std::to_string(busStation->GetLocation());

				// Concatenate hypen.
				if (busStation->GetNext() != nullptr)
				{
					busStationsString += "-";
				}

				// Check if train station also exists on this bus station.
				if (trainStation != nullptr &&
					trainStation->GetLocation() == busStation->GetLocation())
				{
					// Concatenate arrow head.
					if (trainStation->GetLocation() != 0)
					{
						trainStationsString += ">";
					}

					// Concatenate train station.
					trainStationsString += std::to_string(trainStation->GetLocation());

					// Concatenate hyphen.
					if (trainStation->GetNext() != nullptr)
					{
						trainStationsString += "-";
					}

					// Concatenate vertical bar.
					rowAboveBusStations += "|";

					// Go to next train station.
					trainStation = trainStation->GetNext();
				}

				// Concatenate vertical bar.
				rowAboveWalkingStations += "|";

				// Go to next bus station.
				busStation = busStation->GetNext();
			}
		}

		// Adjust length of strings.
		if (m_isScookerLayerAdded == true)
		{
			while (rowAboveScooterStations.length() != walkingStationsString.length())
			{
				rowAboveScooterStations += " ";
			}

			if (scooterStation != nullptr)
			{
				while (scooterStationsString.length() != walkingStationsString.length())
				{
					scooterStationsString += "-";
				}
			}
		}

		while (rowAboveWalkingStations.length() != walkingStationsString.length())
		{
			rowAboveWalkingStations += " ";
		}

		if (busStation != nullptr)
		{
			while (busStationsString.length() != walkingStationsString.length())
			{
				busStationsString += "-";
			}
		}

		while (rowAboveBusStations.length() != walkingStationsString.length())
		{
			rowAboveBusStations += " ";
		}

		if (trainStation != nullptr)
		{
			while (trainStationsString.length() != walkingStationsString.length())
			{
				trainStationsString += "-";
			}
		}

		// Go to next walking station.
		walkingStation = walkingStation->GetNext();
	}

	// Display strings.
	std::cout << trainStationsString << std::endl;
	std::cout << rowAboveBusStations << std::endl;
	std::cout << busStationsString << std::endl;

	if (m_isScookerLayerAdded == true)
	{
		std::cout << rowAboveScooterStations << std::endl;
		std::cout << scooterStationsString << std::endl;
	}

	std::cout << rowAboveWalkingStations << std::endl;
	std::cout << walkingStationsString << std::endl;

	std::cout << std::endl;
}
