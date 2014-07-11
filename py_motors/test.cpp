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
      py.load("testPy");

      // value returned by python is stored here
      //std::string ret = "";
      long ret2 = 0;

      // our argument list that maps string values
      // to their python types
      Arg_map args;
      Arg_map args2;
      args2.clear();
      std::string val;
      std::string val2;
      //double val;
      std::cin >> val;
      //std::cin >> val2;
      printf("Innan argumentpassningen\n");
      // fill up argument strings and their types.

      args2[val] = Py_string;
      printf("Gick förbi py_real\n");
      //args2[val2] = Py_long;

      // make the call
      //py.call("fupp", args2, ret);
      py.call("fupp", args2,ret2);
      printf("lyckades ropa\n");
      //py.call("double", args2, ret2);

      // will print 200
      std::cout << ret2 << '\n';
      //std::cout << ret2 << std::endl;

      return 0;
    }
  catch (Python_exception ex)
    {
      std::cout << ex.what();
    }
  return 0;
}

