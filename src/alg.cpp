// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string line;
  bool novelStarted = false;
  while (std::getline(file, line)) {
    if (!novelStarted) {
      if (line.find("Well, Prince") != std::string::npos) {
        novelStarted = true;
      }
      continue;
    }
    std::string word;
    for (char ch : line) {
      if (std::isalpha(static_cast<unsigned char>(ch))) {
        word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
      } else {
        if (!word.empty()) {
          tree.insert(word);
          word.clear();
        }
      }
    }
    if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  file.close();
}
void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freqs;
  tree.collectFreq(freqs);
  std::sort(freqs.begin(), freqs.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });
  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Cannot open result/freq.txt!" << std::endl;
    return;
  }
  for (const auto& p : freqs) {
    std::cout << p.first << " " << p.second << std::endl;
    out << p.first << " " << p.second << std::endl;
  }
  out.close();
}
