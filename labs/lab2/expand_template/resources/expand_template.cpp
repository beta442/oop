#include "../headers/expand_template.h"
#include "../headers/bohr_trie.h"

template <typename T>
std::vector<T> GetKeyVectorFromMap(const std::map<T, T> map)
{
	std::vector<T> needles;
	needles.resize(std::size(map));
	for (auto it = std::begin(map); it != std::end(map); it++)
	{
		needles.at(std::distance(std::begin(map), it)) = (*it).first;
	}

	return needles;
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	if (std::size(tpl) == 0 || std::size(params) == 0)
	{
		return tpl;
	}
	std::vector<std::string> keys = GetKeyVectorFromMap(params);
	BohrVrtx rootState = InitBohrTrie(keys);
	BohrVrtx* state = &rootState;

	std::string result, collectedSubString;
	for (auto it = std::begin(tpl), end = std::end(tpl); it != end; it++, state = BohrTrieAutoGo(&rootState, state, *it))
	{
		collectedSubString += *it;
		if (state == &rootState)
		{
			result += collectedSubString;
			collectedSubString = "";
		}
		if (state->isTerminal)
		{
			if (it + 1 != end && HasBohrTrieStateNext(state, *(it + 1)))
			{
				continue;
			}
			result += params.at(collectedSubString);
			collectedSubString = "";
			state = &rootState;
		}
	}

	return result;
}
