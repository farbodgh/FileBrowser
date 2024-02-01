#include "SearchingAgent.h"


std::string SearchingAgent::NameOfTheFileToBeSearched;
std::queue<fs::path> SearchingAgent::PathsToBeSearched;
std::ofstream SearchingAgent::errorLog;
std::mutex SearchingAgent::mtx;
bool SearchingAgent::IsFileFound = false;


void SearchingAgent::SearchInitialization(std::string fileNameToBeSearched)
{
	SearchingAgent::NameOfTheFileToBeSearched = fileNameToBeSearched;
	errorLog.open("errorLog.txt", std::ios::trunc);
	if (!errorLog.is_open())
	{
		std::cerr << "Failed to open errorLog.txt for writing.\n";
		exit(1);
	}
}

void SearchingAgent::Searching()
{

}


#ifdef _WIN32
void SearchingAgent::SearchingWithoutMultithreading(std::vector<fs::path>& drives)
{
	//If number of actual concurrent thread is only one
	std::cout << "Agent starts searching for the file" << std::endl;
	for (size_t i = 0; i < drives.size(); ++i)
	{
		for (auto const& file : fs::directory_iterator(drives.at(i)))
		{
			try
			{
				if (file.path().filename() == SearchingAgent::NameOfTheFileToBeSearched)
				{
					std::cout << "File found at " << file.path() << std::endl;
					return;
				}
				else if (file.is_directory())
				{
					this->SearchingWithoutMultithreading(file.path());
					if (this->IsFileFound)
					{
						return;
					}
				}
			}
			catch (const std::exception& e)
			{
				errorLog << "Error: " << file.path() << " could not be accessed because: " << e.what() << std::endl;
			}
			catch (...)
			{
				errorLog <<"Unknown error occurred while accessing " << file.path() << std::endl;
			}
		}
	}
}
#endif // _WIN32

void SearchingAgent::SearchingWithoutMultithreading(fs::path path)
{
	for(auto const& file : fs::directory_iterator(path))
	{
		try
		{
			if (file.path().filename() == SearchingAgent::NameOfTheFileToBeSearched)
			{
				std::cout << "File found at " << file.path() << std::endl;
				this->IsFileFound = true;
				return;
			}
			else if (file.is_directory())
			{
				this->SearchingWithoutMultithreading(file.path());
				if (this->IsFileFound)
				{
					return;
				}
			}
		}
		catch (const std::exception& e)
		{
			errorLog << "Error: " << file.path() << " could not be accessed because: " << e.what() << std::endl;
		}
		catch (...)
		{
			errorLog << "Unknown error occurred while accessing " << file.path() << std::endl;
		}
	}
}


#ifdef __linux__ && __APPLE__

void SearchingAgent::SearchingWithoutMultithreading()
{
	//If number of actual concurrent thread is only one
	fs::path rootPath = "/";
	for (auto const& file : rootPath))
	{
		try
		{
			if (file.path().filename() == SearchingAgent::NameOfTheFileToBeSearched)
			{
				std::cout << "File found at " << file.path() << std::endl;
			}
			else if (file.is_directory())
			{
				this->SearchingWithoutMultithreading(file.path());
			}
		}
		catch (const std::exception&)
		{
		}
		catch (const std::exception&)
		{

		}

	}
}
#endif // __linux__ && __APPLE__