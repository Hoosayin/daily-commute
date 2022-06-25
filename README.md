# Daily Commute – A Concept of Multi-Layered Singly Linked List

#### DESCRIPTION

This is a console app that demonstrates the concept of multi-layered singly linked list. The top layer represents the list of train stations, the middle layer represents the list of bus stations, and the bottom layer represents the list of walking stops. You can walk forward to any station. List of bus stations is a subset of list of walking stops, while list of train stations is a subset of list of bus stations.

#### CLASSES

Following are the classes that are used in this project:

- **Node:** This class represents a station. This station can exist on any layer. It contains pointers to the next node and the down node, and an integral station number. 
- **LinkedList:** This class represents the entire multi-layered linked list. This class contains a pointer to the first train station, i.e. m_trainZero, which is the head node of the list. Let’s explore its methods:
  - **MakeList():** The driver code reads an input file of stations, creates integer arrays of corresponding layers, and passes them to this method. This method initializes head node and creates the nodes using provide integer arrays.
  - **RemoveTrainStation():** This method takes station number as an argument, and removes it from the layer of train stations.
  - **AddBusStation():** This method takes a station number as an argument, and adds it to the layer of bus stations.
  - **BestPath():** This method takes a destination as an argument, and recursively creates the best path to that destination. The best path is the one that takes minimum time to take you to your destination. Top layer is the fastest, while the bottom layer is the slowest. 
  - **AddScooter():** The driver code reads an input file of scooter stops, creates an integer array, and passes that array to this method. This method sandwiches scooter layer between layer of bus stations and layer of walking stops. 
  - **Display():** This method displays the linked list as a graph. 
  - **Copy Constructor:** Copy constructor recursively makes a copy of each node, and creates a similar clone of existing linked list. 
  - **Destructor:** The destructor recursively deletes each node in the linked list.

#### DRIVER CODE

daily-commute.cpp is the entry point of the code. The main function runs a sentinel-controlled loop in which you input different text files to create a linked list and test its methods within the same loop.

- **IDE:** Visual Studio 2022
- **PROGRAMMING LANGUAGE:** c++
- **TOOLSET:** v143 (Also works well on v142)
