#pragma once
#include <regex>
#include <string>

inline std::string incrementTrailingDigits(const std::string& input) {
  std::regex re(R"(\d+$)"); // Match trailing digits
  std::smatch match;

  if (std::regex_search(input, match, re)) {
      int number = std::stoi(match.str()); // Convert matched digits to int
      number++; // Increment the number
      return input.substr(0, match.position()) + std::to_string(number); // Replace with incremented value
  } else {
      return input + "-2";
  }

  return input; // Return unchanged if no digits found
}