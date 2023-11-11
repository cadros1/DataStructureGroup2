#ifndef _HAFFMANCODE_H_
#define _HAFFMANCODE_H_

#include "HaffmanTree.h"
#include <vector>

void calculateWeightFromFile(std::vector<HaffmanTree::Node>* frequenceList,std::string fileName);
std::string askForFileName();
void outputFrequenceList(std::vector<HaffmanTree::Node>* frequenceList);

#endif