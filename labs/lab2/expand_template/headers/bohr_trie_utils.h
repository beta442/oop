#pragma once

#include "bohr_trie.h"

void AddStringIntoBohrTrie(BohrVrtx& root, const std::string& s);
size_t CountWordsInBohrTrie(BohrVrtx& root);
BohrVrtx* GetSuffixLink(BohrVrtx* const root, BohrVrtx* const proccessingVrtx);
BohrVrtx* MakeBohrTrieVertex(BohrVrtx* const parent, const char ancestorEdgeValue);
void StitchBohrTrieWithSuffixLinks(BohrVrtx& root);
