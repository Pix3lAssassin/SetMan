#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

void setFlags(char *arg, int *flags)
{
}

void log(string msg, bool verbose)
{
}

void displayHelp()
{
}

void buildProgram()
{
}

void runCommand()
{
}

template <typename K, typename V>
string mapToString(unordered_map<K, V> &map)
{
  stringstream ss;
  ss << "{";
  for (auto i = map.begin(); i != map.end(); ++i)
  {
    ss << i->first << ":" << i->second;
    if (!(next(i) == map.end()))
    {
      ss << ",";
    }
  }
  ss << "}";

  return ss.str();
}

string vectorToString(vector<string> &vec)
{
  stringstream ss;
  ss << "[";
  for (int i = 0; i < vec.size(); i++)
  {
    if (i != 0)
    {
      ss << ", ";
    }
    ss << vec[i];
  }
  ss << "]";

  return ss.str();
}

void createProject(int argc, char *argv[])
{
  if (argc < 3)
  {
    return;
  }

  char *projectName = nullptr;
  for (int i = 2; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
    }
    else
    {
      projectName = argv[i];
    }
  }

  filesystem::path cwd = filesystem::current_path();

  int status = mkdir("C:/A/", 0777);
  if ((status < 0) && (errno != EEXIST))
  {
    printf("Error creating project directory \n");
  }
}

string flagToOption(char flag)
{
  switch (flag)
  {
  case 't':
    return string("test");
  default:
    return string("invalid");
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    displayHelp();
    return 0;
  }

  const string INVALID("invalid");
  unordered_map<char, bool> flags;
  unordered_map<string, string> options;
  vector<string> args;

  for (int i = 1; i < argc; i++)
  {
    string arg(argv[i]);
    cout << arg << endl;
    int arglen = arg.length();

    // Flags
    if (arglen >= 2 && arg.at(0) == '-')
    {
      string optFlag{};
      string optValue{};

      if (arglen == 2) // ex. "-r"
      {
        optFlag = flagToOption(arg.at(1));
        if (optFlag.size() < 2 || optFlag == INVALID)
        {
          flags[arg.at(1)] = true;
        }
      }
      else if (arglen >= 3 && arg.at(1) == '-') // ex. "--a"
      {
        int equalLoc = arg.find_first_of('=', 2);
        if (equalLoc != string::npos)
        { // ex. "--foo=bar"
          optFlag = arg.substr(2, equalLoc);
          optValue = arg.substr(equalLoc + 1);
        }
        else
        { // ex. "--help"
          optFlag = arg.substr(2);
        }
      }
      else
      { // ex. "-abc"
        for (int charIndex = 1; charIndex < arglen; charIndex++)
        {
          flags[arg.at(charIndex)] = true;
        }
      }

      // Peek forward in arguments arr if flag requires user input
      if (optFlag.size() != 0 && optFlag != INVALID && i < argc - 1 && i > 1)
      {
        // If we captured a flag and value store them in the options map
        if (optValue.size() != 0)
        {
          options[optFlag] = optValue;
          continue;
        }

        string next(argv[++i]);
        if (next.length() > 0 && next.at(0) != '-')
        {
          options[optFlag] = next;
          continue;
        }
        else
        {
          stringstream ss;

          ss << "Invalid option at: " << arg.c_str() << " " << next.c_str();

          throw invalid_argument(ss.str().c_str());
        }
      }
    }
    else
    {
      args.push_back(arg);
    }
  }

  cout << "Args: " << vectorToString(args) << endl;
  cout << "Flags: " << mapToString<char, bool>(flags) << endl;
  cout << "Options: " << mapToString<string, string>(options) << endl;

  // if (strcmp(argv[1], "build") == 0)
  // {
  //   buildProgram();
  // }

  // if (strcmp(argv[1], "run") == 0)
  // {
  //   runCommand();
  // }

  // if (strcmp(argv[1], "create") == 0)
  // {
  //   createProject(argc, argv);
  // }

  // if (argv[1][0] == '-')
  // {
  //   displayHelp();
  // }
}