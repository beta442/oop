#pragma once

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>

struct BohrVrtx
{
	size_t wordNumber;
	bool isWordEnd;
	std::vector<BohrVrtx*> nextVrtx;
	BohrVrtx* parentLink;
	BohrVrtx* suffixLink;
	char edgeFromAncestor;
};

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);

BohrVrtx InitBohrTrie();
void AddStringIntoBohrTrie(BohrVrtx& root, const std::string& s);
void PrintBohrTrie(BohrVrtx& root, std::vector<char>& collectedWord);
bool IsStringInBohrTrie(BohrVrtx& root, const std::string& s);
size_t CountWordsInBohrTrie(BohrVrtx& root);
void StitchBohrTrieWithSuffixLinks(BohrVrtx& root);
