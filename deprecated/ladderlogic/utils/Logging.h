#pragma once

//This module is responsible for logging every action taken during runtime of the program.

#include <iostream>
#include <iomanip>
#include <chrono> //For keeping track of time.
#include <fstream> //For reading, writing and modifying files.
#include <ctime> //Additional time functionality.

//#define LOG Logging //For quicker code writing and better readability.

//static bool logCreated;

class Logging {
public:
				std::string logFileName; //This variable stores the name of a new file. Generally this is for testing purposes.
				int counter; //For counting each logged action.
				std::fstream logFile; //For writing, reading and modifying log files.
				std::chrono::duration<float> lifespanoflog; //For calculating the amount of time the program has been running.

				std::chrono::time_point<std::chrono::steady_clock> loglifetimestart; //For storing the time a log file has been created. (Usually at the startup of the program.)
				std::chrono::time_point<std::chrono::steady_clock> loglifetimeend; //For storing the time at which our log file has been deleted. (Usually at the end of the program runtime.)
				Logging();

				explicit Logging(
								std::string filename); //For creating a new log file with a custom name. !EXPERIMENTAL! - This is meant for testing purposes

				~Logging();

				static std::string Get_Now_Timer(); //Function for getting the current time and date at the requested runtime.

				void Log_Action(); //Function gets called by other modules to call PTF of execution.

				void Read_Log(); //Function to print the whole of log to console and make its readability easier.

				//String only prints:

				void PTF(const std::string &Print1); //Print to file function.
				void PTF(const std::string &Print1, const std::string &Print2); //Print to file function.
				void PTF(const std::string &Print1, const std::string &Print2, const std::string &Print3);

				void
				PTF(const std::string &Print1, const std::string &Print2, const std::string &Print3, const std::string &Print4);

				void PTF(const std::string &Print1, const std::string &Print2, const std::string &Print3, const std::string &Print4,
													const std::string &Print5);

				//Int only prints:

				void PTF(int Print1);

				void PTF(int Print1, int Print2);

				void PTF(int Print1, int Print2, int Print3);

				void PTF(int Print1, int Print2, int Print3, int Print4);

				void PTF(int Print1, int Print2, int Print3, int Print4, int Print5);

				//Float only prints:

				void PTF(float Print1);

				//String and float prints:

				void PTF(float Print1, const std::string &Print2);

				void PTF(float Print1, const std::string &Print2, int setprecs);

				void PTF(float Print1, const std::string &Print2, const std::string &Print3, int setprecs);

				void PTF(const std::string &Print1, float Print2, const std::string &Print3, int setprecs);

				//String and int prints:

				void PTF(const std::string &Print1, int Print2);

				void PTF(int Print1, const std::string &Print2);

				void PTF(const std::string &Print1, int Print2, const std::string &Print3);

				void PTF(int Print1, const std::string &Print2, const std::string &Print3);

				void PTF(const std::string &Print1, const std::string &Print2, int Print3);

				void PTF(const std::string &Print1, int Print2, const std::string &Print3, int Print4, const std::string &Print5);

				void PTF(const std::string &Print1, int Print2, const std::string &Print3, int Print4, const std::string &Print5,
													int Print6);

				void PTF(const std::string &Print1, int Print2, const std::string &Print3, int Print4, const std::string &Print5,
													int Print6, const std::string &Print7);

				void PTF(const std::string &Print1, int Print2,
													const std::string &Print3, const std::string &Print4, const std::string &Print5);

				void PTF(const std::string &Print1, const std::string &Print2,
													const std::string &Print3, int Print4, const std::string &Print5);

				void PTF(const std::string &Print1, const std::string &Print2,
													const std::string &Print3, int Print4);

};