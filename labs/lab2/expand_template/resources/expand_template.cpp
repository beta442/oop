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
	const std::vector<std::string> keys = GetKeyVectorFromMap(params);
	BohrVrtx rootState = InitBohrTrie(keys);
	BohrVrtx* state = &rootState;
	std::map<std::string, std::string> newParamsForFailPrefix{};

	std::string result, collectedPrefix;
	bool isNextStateAtSamePrefix = false;
	for (auto it = std::begin(tpl), end = std::end(tpl); it != end; it++)
	{
		state = BohrTrieAutoGo(&rootState, state, *it);
		collectedPrefix += *it;

		if (state == &rootState)
		{
			result += collectedPrefix;
			collectedPrefix = "";
			continue;
		}

		isNextStateAtSamePrefix = it + 1 != end && HasBohrTrieStateNext(state, *(it + 1));
		if (state->isTerminal && isNextStateAtSamePrefix)
		{
			newParamsForFailPrefix[collectedPrefix] = params.at(collectedPrefix);
		}
		else if (state->isTerminal && !isNextStateAtSamePrefix)
		{
			if (params.find(collectedPrefix) != std::end(params))
			{
				result += params.at(collectedPrefix);
			}
			else
			{
				result += ExpandTemplate(collectedPrefix.substr(0, std::size(collectedPrefix) - 1), newParamsForFailPrefix);
				newParamsForFailPrefix.empty();
				it--;
				collectedPrefix = "";
				state = &rootState;
				continue;
			}

			collectedPrefix = "";
			state = &rootState;
		}
	}

	return result;
}
