#pragma once

#include "std_libs.h"

struct BohrVrtx
{
	char ancestorEdgeValue;
	size_t wordNumber;
	bool isTerminal;
	std::vector<BohrVrtx*> nextVrtx;
	BohrVrtx* parentLink;
	BohrVrtx* suffixLink;
};

BohrVrtx* BohrTrieAutoGo(BohrVrtx* const root, const BohrVrtx* currState, char nextState);
bool HasBohrTrieStateNext(const BohrVrtx* const state, const char nextState);
BohrVrtx InitBohrTrie(const std::vector<std::string>& searchStringVector);
