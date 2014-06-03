#include <iostream>

#include "pyembed.h"
using namespace pyembed; // for brevity

// our unit test function
static void run_test(int argc, char** argv);

int
main(int argc, char** argv)
{
  run_test(argc, argv);
  return 0;
}

void
run_test(int argc, char** argv)
{
  try
    {
      // Ok. Now we can create an instance of the interprter itself.
      Python py(argc, argv);

      // to check if the python interpreter is available and working,
      // execute a simple python statement.
      py.run_string("print 'Hello world from Python!'");

      // execute the script in a file
      py.run_file("hello.py");
      
      // Load the test module into the interpreter
      py.load("test");

      // Call a simple function, that takes no arguments
      // and returns nothing      
      py.call("simple");


      Arg_map args; // our argument list that maps string values 
                    // to their python types     

      // Call a function that takes two long arguments and returns
      // a long      
      {
	long ret = 0; // value returned by python is stored here
	args["10"] = Py_long;
	args["20"] = Py_long;
	py.call("multiply", args, ret);
	std::cout << ret << '\n';
	args.clear();
      }      

      // call a function a takes a string and just echoes it
      {
	std::string ret = "";
	args["Hello from C++"] = Py_string;
	py.call("echo", args, ret);
	std::cout << ret << '\n';
	args.clear();
      }

      // call a function that returns a list
      {
	String_list ret;
	py.call("names_as_list", args, ret);
	size_t sz = ret.size();
	for (size_t i=0; i<sz; i++)
	  std::cout << ret[i] << '\t';
	std::cout << '\n';
      }

      // call a function that returns a tuple
      {
	String_list ret;
	py.call("names_as_tuple", args, ret);
	size_t sz = ret.size();
	for (size_t i=0; i<sz; i++)
	  std::cout << ret[i] << '\t';
	std::cout << '\n';
      }

      // call a function that returns a dictionary
      {
	String_map ret;
	py.call("config", args, ret);
	String_map::const_iterator it;
	for (it = ret.begin(); it != ret.end(); it++)
	  std::cout << it->first << ':' << it->second << '\t';
	std::cout << '\n';
      }

    }
  catch (Python_exception ex)
    {
      std::cout << ex.what() << '\n';
    }
}
