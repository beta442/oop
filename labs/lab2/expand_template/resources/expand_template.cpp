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

	std::string result, collectedPrefix;
	//TODO: find all search substring in fail collectedPrefix
	std::vector<const std::string*> collectedTerminalStates;
	bool isNextStateAtSamePrefix = false;
	for (auto it = std::begin(tpl), end = std::end(tpl); it != end; it++)
	{
		state = BohrTrieAutoGo(&rootState, state, *it);
		collectedPrefix += *it;

		if (state == &rootState)
		{
			collectedTerminalStates.clear();
			result += collectedPrefix;
			collectedPrefix = "";
			continue;
		}

		isNextStateAtSamePrefix = it + 1 != end && HasBohrTrieStateNext(state, *(it + 1));
		if (state->isTerminal && isNextStateAtSamePrefix)
		{
			//collectedTerminalStates.at(std::size(collectedTerminalStates) - 1) = &params.at(collectedPrefix);
		}
		else if (!isNextStateAtSamePrefix)
		{
			if (params.find(collectedPrefix) != std::end(params))
			{
				result += params.at(collectedPrefix);
			}
			else
			{
				result += collectedPrefix;
				/*auto resultEndIt = std::end(result) - 1;
				for (auto ch : collectedPrefix)
				{
					result += " ";
				}

				size_t collectedPrefixIndex = std::size(collectedPrefix) - 1;
				for (auto cTSBegIt = std::begin(collectedPrefix), cTSEndIt = std::end(collectedPrefix);
					 cTSEndIt != cTSBegIt; cTSEndIt--, collectedPrefixIndex--)
				{
					if (auto indexOfTerminalStateInCollectedPrefix = std::distance(cTSBegIt, cTSEndIt);
						collectedTerminalStates.at(indexOfTerminalStateInCollectedPrefix) != nullptr)
					{
					}
					else
					{
						result.at(std::distance(resultEndIt, it + collectedPrefixIndex)) += collectedPrefix.at(collectedPrefixIndex);
					}
				}*/
			}

			collectedTerminalStates.clear();
			collectedPrefix = "";
			state = &rootState;
		}
	}

	return result;
}
