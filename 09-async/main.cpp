#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>

using namespace std::chrono;

std::string fetchDataFromDB(std::string recvdData)
{
  // Make sure that function takes 5 seconds to complete
  std::this_thread::sleep_for(seconds(5));
  //Do stuff like creating DB Connection and fetching Data
  return "DB_" + recvdData;
}

std::string fetchDataFromFile(std::string recvdData)
{
  // Make sure that function takes 3 seconds to complete
  std::this_thread::sleep_for(seconds(3));
  //Do stuff like fetching Data File
  return "File_" + recvdData;
}


int main()
{
  std::cout << "Hello" << std::endl;

  std::cout << "Just using call 2 functions sequentialy." << std::endl;
  // Get Start Time
  system_clock::time_point start = system_clock::now();

  //Fetch Data from DB
  std::string dbData = fetchDataFromDB("Data");
  //Fetch Data from File
  std::string fileData = fetchDataFromFile("Data");

  // Get End Time
  auto end = system_clock::now();
  auto diff = duration_cast < std::chrono::seconds > (end - start).count();
  std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;
  
  //Combine The Data
  std::string data = dbData + " :: " + fileData;
  //Printing the combined Data
  std::cout << "Data = " << data << std::endl;

// ******* Async using *********
  std::cout << std::endl;
  std::cout << "Call 2 functions in parallel threads." << std::endl;
 
  start = system_clock::now();

  auto resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
  auto resultFromFile = std::async(std::launch::async, fetchDataFromFile, "Data");

  // Will block till data is available in future<std::string> object.
  dbData = resultFromDB.get();
  fileData = resultFromFile.get();
 
  // Get End Time
  end = system_clock::now();
  diff = duration_cast < std::chrono::seconds > (end - start).count();
  std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;

  //Combine The Data
  data = dbData + " :: " + fileData;
  //Printing the combined Data
  std::cout << "Data = " << data << std::endl;

// ***************** Other async using *****************
  std::cout << std::endl;
  std::cout << "Call lambda function in parallel thread." << std::endl;

  auto resultLambda = std::async([](std::string name){
		    std::this_thread::sleep_for (seconds(4));
  		    return "Hello " + name;
		  }, "Sasha");

  auto rl = resultLambda.get();
  std::cout << rl << std::endl;

  return 0;
}

