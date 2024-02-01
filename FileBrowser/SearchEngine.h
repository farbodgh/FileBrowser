#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

enum class Platfrom
{
	Windows,
	Linux,
	Mac
};

class SearchEngine
{
public:
	SearchEngine(const std::string& fileName) : fileToBeSearched(fileName)
	{
		CommonInit();
	}

	SearchEngine(const std::string&& fileName) : fileToBeSearched(fileName) 
	{
		CommonInit();
	}


	void Search();
	void LocalSearch(const std::string fileName = "");
	void SearchFromPath(fs::path pathToStartTheSearch, const std::string& fileName);
	
	
private:
		void Analyze();
		Platfrom platform;
		std::string fileToBeSearched;
		std::vector<fs::path> pathsToBeSearched;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> endTime;
		size_t numberOfActuallConcurrentThreads;
		bool isFileFound{ false };
		bool isAgentWorking{ false };

		void CommonInit();

#ifdef _WIN32
		std::vector<fs::path> drives;
#endif 

#ifdef __linux__ && __APPLE__
		fs::path root;
#endif


};

