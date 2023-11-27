#ifndef _HAFFMANCODE_H_
#define _HAFFMANCODE_H_

#include "HaffmanTree.h"
#include <vector>
#include <string>

using namespace std;

void calculateWeightFromFile(HaffmanTree* tree,std::string fileName);
std::string askForFileName();
void outputFrequenceList(HaffmanTree* tree);

#endif