#pragma once

#ifndef __MESSAGE_RECORDING_HPP__
#define __MESSAGE_RECORDING_HPP__


#include <iostream>


inline void RecordErrorMessage(const std::string& message)
{
	// Replace with the desired output.
	// For example, when adding a logging system.
	std::cerr << "ERROR: " << message << std::endl;
}


inline void RecordInfoMessage(const std::string& message)
{
	// Replace with the desired output.
	// For example, when adding a logging system.
	std::cout << "INFO: " << message << std::endl;
}


#endif // ! __MESSAGE_RECORDING_HPP__
