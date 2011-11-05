#include<exception>
using namespace std;

class ParseException: public exception
{
  virtual const char* what() const throw()
  {
    return "Parse Error!";
  }
};

