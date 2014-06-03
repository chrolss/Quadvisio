#include <iostream>
#include <vector>
using std::cout;
using std::cin;

#include "pyembed.h"

static void print_menu();
static void list_users();

// this is the only function that should interest you.
// all python calls go here
static void add_user();

// data of users created using the UI are stored here
// in a simple text format
static std::vector<std::string> users;

static int global_argc;
static char** global_argv;

int
main(int argc, char** argv)
{
  global_argc = argc;
  global_argv = argv;
  print_menu();
  return 0;
}

void
print_menu()
{
  cout << "1. List users\n";
  cout << "2. Add user\n";
  cout << "3. Quit\n";
  cout << ">> ";
  int option = 0;
  cin >> option;
  switch (option)
    {
    case 1:
      list_users();
      break;
    case 2:
      add_user();
      break;
    case 3:
      exit(0);
      break;
    default:
      cout << "Not a valid option.\n";
    }
  print_menu();
}

void
list_users()
{
  size_t s = users.size();
  for (size_t i=0; i<s; i++)
    cout << users[i] << '\n';
  cout << '\n';
}

void
add_user()
{
  try
    {
      pyembed::Python python(global_argc, global_argv);
      python.load("adduserform");

      // call the python function that creates and displays the GUI
      pyembed::String_map ret; // attributes of the new user are returned here
      pyembed::Arg_map args; // our empty argument list
      python.call("show_win", args, ret);

      if (ret.size() <= 1) // the user clicked cancel
	return;

      // create a single string from the returned map
      // and add it to the users list
      std::string user = "";
      pyembed::String_map::const_iterator it;
      for (it = ret.begin(); it != ret.end(); it++)
	{
	  user += '[';
	  user += it->first;
	  user += ':';
	  user += it->second;
	  user += ']';
	}
      users.push_back(user);
    }
  catch (pyembed::Python_exception ex)
    {
      cout << "Python error: " << ex.what() << '\n';
    }
}


