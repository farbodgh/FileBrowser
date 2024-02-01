#include "SearchEngine.h"
#include "SearchingAgent.h"

#include <filesystem>
#include <iostream>
#include <thread>

namespace fs = std::filesystem;


//This method is used to execute common codes inside the constructors.
void SearchEngine::CommonInit()
{
	this->startTime = std::chrono::steady_clock::now();
}

/// <summary>
/// This method is the initializer of the search.
/// It sotres all useful information such as the number of actual concurrent threads, the name of the file to be searched, the paths to be searched and the drives to be searcheds, platform, and if windows the number of drives
/// </summary>
void SearchEngine::Analyze()
{
#ifdef _WIN32
	this->platform = Platfrom::Windows;
	//If the platform is windows, then we should find all drives.
	for (char drive = 'A'; drive <= 'Z'; ++drive) 
	{
		std::string drivePath = std::string(1, drive) + ":\\";
		if (std::filesystem::exists(drivePath))
		{
			drives.push_back(drivePath);
		}
	}
#elif __linux__
	this->platform = Platfrom::Linux;
#elif __APPLE__
	this->platform = Platfrom::Mac;
#endif

//Now it should know how many actual concurrent threads exist in the OS

this->numberOfActuallConcurrentThreads = std::thread::hardware_concurrency();
}


void SearchEngine::Search()
{
	Analyze();
#ifdef _WIN32

	if (this->platform == Platfrom::Windows)
	{
		SearchingAgent::SearchInitialization(this->fileToBeSearched);
		SearchingAgent agent;
		//If the number of actual concurrent threads is less than 2, then we should use only one thread.	
		if(this->numberOfActuallConcurrentThreads < 2)
		{
			agent.SearchingWithoutMultithreading(drives);
		}
		endTime = std::chrono::steady_clock::now();
		std::cout <<std::endl << "The search has finished." << std::endl;
		std::cout << "The process tooks " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " seconds." << std::endl;
		return;
	}
#endif

#ifdef __linux__ && __APPLE__
	
#endif 

}

