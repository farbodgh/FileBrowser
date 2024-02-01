#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <thread>
#include <queue>
#include <mutex>
namespace fs = std::filesystem;

/// <summary>
/// This class creates agents that search for a file in a given path and its subdirectories.
/// </summary>
class SearchingAgent
{
public:

	static void SearchInitialization(std::string fileNameToBeSearched);
	SearchingAgent(fs::path initialPathToBeSearched) : pathToBeSearched(initialPathToBeSearched) {}
	SearchingAgent() {};
	void Searching();
	
#ifdef _WIN32
	void SearchingWithoutMultithreading(std::vector<fs::path>& drives);
#endif 

#ifdef __linux__ && __APPLE__
	void SearchingWithoutMultithreading();
#endif
	

private:
	static std::string NameOfTheFileToBeSearched;
	static std::queue<fs::path> PathsToBeSearched;
	static bool IsFileFound;
	static std::ofstream errorLog;
	static std::mutex mtx;
	fs::path pathToBeSearched;

	void SearchingWithoutMultithreading(fs::path pathToBeSearched);
	void CommonInit();



};

