#include <iostream>
#include "pyembed.h"
#include <string>
using namespace pyembed; // for brevity

int
main(int argc, char** argv)
{
  try // always check for Python_exceptions
    {

      // Create an instance of the interpreter.
      Python py(argc, argv);

      // Load the test module into the interpreter
      py.load("test");

      // value returned by python is stored here
      long ret = 0;

      // our argument list that maps string values
      // to their python types
      Arg_map args;

      std::string val;
      std::string val2;

      for (int i=0; i<10; i++){
    	  std::cin >> val;
    	  std::cin >> val2;
    	  // fill up argument strings and their types.
    	  args[val] = Py_long;
    	  args[val2] = Py_long;

    	  // make the call
    	  py.call("spit", args,ret);
    	  args.clear();

      std::cout << ret << '\n';
      }
      return 0;
    }
  catch (Python_exception ex)
    {
      std::cout << ex.what();
    }
  return 0;
}
