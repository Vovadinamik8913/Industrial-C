#include <iostream>
#include <libregex/exception.hpp>
#include <libregex/matcher.hpp>
#include <libregex/parser.hpp>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "not enough arguments" << std::endl;
  }

  std::string regexp(argv[1]);
  try {
    libregex::parser regexp_parser(regexp);
    libregex::matcher match_system(regexp_parser.parse());
    std::string check;
    while (!std::cin.eof()) {
      std::getline(std::cin, check);
      try {
        bool res = match_system.full_match(check);
        std::cout << res << std::endl;
      } catch (const libregex::regex_exception &e) {
        std::cerr << e.what() << std::endl;
        std::cout << false << std::endl;
      }
    }
  } catch (const libregex::regex_exception &e) {
    std::cerr << e.what() << std::endl;
  }
}