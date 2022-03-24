#include "../headers/bohr_trie.h"
#include "../headers/bohr_trie_utils.h"

void AddStringIntoBohrTrie(BohrVrtx& root, const std::string& s)
{
	BohrVrtx* bohrTriePtr = &root;
	size_t wordAmountBeforeInsertion = CountWordsInBohrTrie(root);
	for (auto it = std::begin(s); it != std::end(s); ++it)
	{
		if (!bohrTriePtr->nextVrtx[*it])
		{
			bohrTriePtr->nextVrtx[*it] = MakeBohrTrieVertex(bohrTriePtr, *it);
		}
		bohrTriePtr = bohrTriePtr->nextVrtx[*it];
	}
	if (bohrTriePtr != &root)
	{
		bohrTriePtr->isTerminal = true;
		bohrTriePtr->wordNumber = CountWordsInBohrTrie(root) - 1;
	}
}

BohrVrtx* BohrTrieAutoGo(BohrVrtx* const root, const BohrVrtx* currState, char nextState)
{
	while (currState)
	{
		if (currState->nextVrtx[nextState])
		{
			return currState->nextVrtx[nextState];
		}
		else if (currState == root)
		{
			break;
		}
		currState = currState->suffixLink;
	}
	return root;
}

size_t CountWordsInBohrTrie(BohrVrtx& root)
{
	size_t result = 0;
	for (auto it = std::begin(root.nextVrtx); it != std::end(root.nextVrtx); it++)
	{
		if (*it)
		{
			if ((*it)->isTerminal)
			{
				result++;
			}
			result += CountWordsInBohrTrie(*(*it));
		}
	}
	return result;
}

BohrVrtx* GetSuffixLink(BohrVrtx* const root, BohrVrtx* const proccessingVrtx)
{
	if (proccessingVrtx == root || proccessingVrtx->parentLink == root)
	{
		return root;
	}
	else
	{
		return BohrTrieAutoGo(root, proccessingVrtx->parentLink->suffixLink, proccessingVrtx->ancestorEdgeValue);
	}
}

bool HasBohrTrieStateNext(const BohrVrtx* const state, const char nextState)
{
	if (!state)
	{
		return false;
	}
	if (nextState >= 0 && state->nextVrtx[nextState])
	{
		return true;
	}
	return false;
}

constexpr size_t ASCII_CP_SIZE = 256;

BohrVrtx* MakeBohrTrieVertex(BohrVrtx* const parent = nullptr, const char ancestorEdgeValue = -1)
{
	BohrVrtx* v = new BohrVrtx;
	v->wordNumber = -1;
	v->isTerminal = false;
	v->nextVrtx.assign(ASCII_CP_SIZE, nullptr);
	v->parentLink = parent;
	v->suffixLink = nullptr;
	v->ancestorEdgeValue = ancestorEdgeValue;
	return v;
}

BohrVrtx InitBohrTrie(const std::vector<std::string>& searchStringVector)
{
	BohrVrtx root = *MakeBohrTrieVertex();
	for (auto it = std::begin(searchStringVector); it != std::end(searchStringVector); it++)
	{
		AddStringIntoBohrTrie(root, *it);
	}
	StitchBohrTrieWithSuffixLinks(root);

	return root; //выделил справа тест-проект, там импорчу .h из основного проекта, где разрабатывал
}

void StitchBohrTrieWithSuffixLinks(BohrVrtx& root)
{
	std::list<BohrVrtx*> bohrVrtxQueue;
	bohrVrtxQueue.push_back(&root);

	BohrVrtx* proccessingVrtx;
	while (!bohrVrtxQueue.empty())
	{
		proccessingVrtx = bohrVrtxQueue.front();
		bohrVrtxQueue.pop_front();

		proccessingVrtx->suffixLink = GetSuffixLink(&root, proccessingVrtx);

		for (auto it = std::begin(proccessingVrtx->nextVrtx); it != std::end(proccessingVrtx->nextVrtx); it++)
		{
			if (*it)
			{
				bohrVrtxQueue.push_back(*it);
			}
		}
	}
}
