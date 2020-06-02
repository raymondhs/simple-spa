#pragma once
#include <exception>
#include <string>

class ParseException: public std::exception
{
std::string message;

  virtual const char* what() const throw()
  {
    return message.c_str();
  }
public:
	ParseException(std::string m) { message = m; }
	ParseException() { message = "Match Exception Occured"; }
} ;

