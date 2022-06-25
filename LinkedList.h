#pragma once

#include "Node.h"
#include <fstream>

class LinkedList
{
private:
	bool m_isScookerLayerAdded{ false };
	Node* m_trainZero{ nullptr };

	void SetTrainZero();
	void CreateBestPathStationString(Node* station, std::string& stationString, Node*& lastStation);
	void DisplayBestPath(Node* bestPath);

	void DeleteStation(Node* station);
	Node* GetBestPathStation(Node* station, int destination);
	Node* DeepCopy(Node* other);

	bool IsDistantThanLastWalkingStation(int location);
public:
	LinkedList();
	LinkedList(const LinkedList& other);
	virtual ~LinkedList();

	void operator =(const LinkedList& other);

	void MakeList(
		int* trainStations,
		int* busStations,
		int* walkingStations,
		int numberOfWalkingStations);

	void AddScooter(
		int* scooterStations,
		int numberOfScooterStations);

	void RemoveTrainStation(int location);

	void AddBusStation(int location);

	Node* BestPath(int destination);

	void Display();
};

