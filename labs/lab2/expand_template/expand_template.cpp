#include "expand_template.h"

constexpr size_t ASCII_CP_SIZE = 255;

BohrVrtx* MakeBohrTrieVertex(BohrVrtx* parent = nullptr, char edgeFromAncestor = -1)
{
	BohrVrtx* v = new BohrVrtx;
	v->wordNumber = -1;
	v->isWordEnd = false;
	v->nextVrtx.assign(ASCII_CP_SIZE, nullptr);
	v->parentLink = parent;
	v->suffixLink = nullptr;
	v->edgeFromAncestor = edgeFromAncestor;
	return v;
}

BohrVrtx InitBohrTrie()
{
	return *MakeBohrTrieVertex();
}

size_t CountWordsInBohrTrie(BohrVrtx& root);

void AddStringIntoBohrTrie(BohrVrtx& root, const std::string& s)
{
	BohrVrtx* bohrTriePtr = &root;
	for (size_t i = 0; i < std::size(s); ++i)
	{
		if (!bohrTriePtr->nextVrtx[s[i]])
		{
			bohrTriePtr->nextVrtx[s[i]] = MakeBohrTrieVertex(bohrTriePtr, s[i]);
			// std::cout << "For '" << bohrTriePtr->nextVrtx[s[i]]->edgeFromAncestor << "' parent is '" << bohrTriePtr->nextVrtx[s[i]]->parentLink->edgeFromAncestor << "'" << std::endl;
		}
		bohrTriePtr = bohrTriePtr->nextVrtx[s[i]];
	}
	bohrTriePtr->isWordEnd = true;
	bohrTriePtr->wordNumber = CountWordsInBohrTrie(root) - 1;
}

size_t CountWordsInBohrTrie(BohrVrtx& root)
{
	size_t result = 0;
	for (size_t i = 0; i < std::size(root.nextVrtx); i++)
	{
		if (root.nextVrtx[i])
		{
			if (root.nextVrtx[i]->isWordEnd)
			{
				result++;
			}
			result += CountWordsInBohrTrie(*(root.nextVrtx[i]));
		}
	}
	return result;
}

void PrintBohrTrie(BohrVrtx& root, std::vector<char>& collectedWord)
{
	for (size_t i = 0; i < std::size(root.nextVrtx); i++)
	{
		if (root.nextVrtx[i])
		{
			collectedWord.push_back(static_cast<char>(i));
			if (root.nextVrtx[i]->isWordEnd)
			{
				for (size_t i = 0; i < collectedWord.size(); i++)
				{
					std::cout << collectedWord[i];
				}
				std::cout << std::endl;
			}
			PrintBohrTrie(*(root.nextVrtx[i]), collectedWord);
			collectedWord.resize(std::size(collectedWord) - 1);
		}
	}
}

bool IsStringInBohrTrie(BohrVrtx& root, const std::string& s)
{
	BohrVrtx* bohrTriePtr = &root;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!bohrTriePtr->nextVrtx[s[i]])
		{
			return false;
		}
		bohrTriePtr = bohrTriePtr->nextVrtx[s[i]];
	}
	return true;
}

void StitchVertex(BohrVrtx& root, BohrVrtx& proccessingVrtx);

void StitchBohrTrieWithSuffixLinks(BohrVrtx& root)
{
	std::list<BohrVrtx> bohrVrtxQueue;
	bohrVrtxQueue.push_back(root);

	BohrVrtx proccessingVrtx;
	while (!bohrVrtxQueue.empty())
	{
		proccessingVrtx = bohrVrtxQueue.front();
		bohrVrtxQueue.pop_front();

		std::cout << "Parent link is:" << proccessingVrtx.parentLink << std::endl;
		std::cout << "Before suffix_link:" << proccessingVrtx.suffixLink << " ";

		StitchVertex(root, proccessingVrtx);

		std::cout << "Now suffix_link is:" << proccessingVrtx.suffixLink << std::endl;

		 std::cout << "Suffix link for '" << proccessingVrtx.edgeFromAncestor << "' is ";
		 if (proccessingVrtx.suffixLink == nullptr)
		{
			std::cout << "root";
		 }
		 else
		{
			//std::cout << proccessingVrtx.suffixLink << " " << &root << "'";
			std::cout << proccessingVrtx.suffixLink->edgeFromAncestor;
		 }
		 std::cout << std::endl;

		for (size_t i = 0; i < std::size(proccessingVrtx.nextVrtx); i++)
		{
			if (proccessingVrtx.nextVrtx[i])
			{
				bohrVrtxQueue.push_back((*proccessingVrtx.nextVrtx[i]));
			}
		}
	}
}

void StitchVertex(BohrVrtx& root, BohrVrtx& proccessingVrtx)
{
	if (proccessingVrtx.parentLink == nullptr)
	{
		proccessingVrtx.suffixLink = &root;
		return;
	}
	BohrVrtx* parent = proccessingVrtx.parentLink;
	const char searchEdge = proccessingVrtx.edgeFromAncestor;

	BohrVrtx* proccessingSuffixLink = parent->suffixLink;
	std::cout << "For edge '" << searchEdge << "' :";
	std::cout << " parent suffixLink:" << parent->suffixLink << std::endl;
	while (proccessingSuffixLink)
	{
		if (proccessingSuffixLink->nextVrtx[searchEdge])
		{
			proccessingVrtx.suffixLink = proccessingSuffixLink->nextVrtx[searchEdge];
			return;
		}
		proccessingSuffixLink = proccessingSuffixLink->suffixLink;
	}
	parent->suffixLink = &root;
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	return "";
}
