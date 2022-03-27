#include "../headers/expand_template.h"
#include "../headers/bohr_trie.h"

template <typename T>
std::vector<T> GetKeyVectorFromMap(const std::map<T, T> map)
{
	std::vector<T> keys;
	keys.resize(std::size(map));
	for (auto it = std::begin(map); it != std::end(map); it++)
	{
		keys.at(std::distance(std::begin(map), it)) = (*it).first;
	}

	return keys;
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	if (std::size(tpl) == 0 || std::size(params) == 0)
	{
		return tpl;
	}
	const std::vector<std::string> keys = GetKeyVectorFromMap(params);
	BohrVrtx rootState = InitBohrTrie(keys);
	std::cout << "Bohr trie init" << std::endl;
	BohrVrtx* state = &rootState;
	std::map<std::string, std::string> newParamsForFailPrefix{};

	std::string result, collectedPrefix, reversedBufferFirst, reversedBufferSecond;
	bool isNextStateAtSamePrefix = false;
	for (auto it = std::begin(tpl), end = std::end(tpl); it != end; it++)
	{
		state = BohrTrieAutoGo(&rootState, state, *it);
		collectedPrefix += *it;
		std::cout << "Collected:'" << collectedPrefix << "'" << std::endl;

		if (state == &rootState)
		{
			result += collectedPrefix;
			collectedPrefix = "";
			std::cout << "State is root, result:'" << result << "'" << std::endl;
			continue;
		}

		isNextStateAtSamePrefix = it + 1 != end && HasBohrTrieStateNext(state, *(it + 1));
		std::cout << *it << "-" << ((it + 1) != end ? *(it + 1) : '!') << "- has:" << HasBohrTrieStateNext(state, *(it + 1)) << " size:" << std::size(newParamsForFailPrefix) << std::endl;
		if (state->isTerminal && isNextStateAtSamePrefix)
		{
			std::cout << "Keep collecting same prefix" << std::endl;
			reversedBufferFirst = collectedPrefix;
			if (params.find(collectedPrefix) != std::end(params))
			{
				reversedBufferSecond = params.at(collectedPrefix);

				std::reverse(std::begin(reversedBufferFirst), std::end(reversedBufferFirst));
				std::reverse(std::begin(reversedBufferSecond), std::end(reversedBufferSecond));
				newParamsForFailPrefix[reversedBufferFirst] = reversedBufferSecond;
				std::cout << "Inserted pair in new map" << std::endl;
			}
		}
		else if (state->isTerminal && !isNextStateAtSamePrefix || // collected prefix
			!isNextStateAtSamePrefix && std::size(newParamsForFailPrefix) ||
			it + 1 == end && std::size(collectedPrefix)) // collected prefix at the tpl's end
		{
			std::cout << "Need to replace" << std::endl;
			if (params.find(collectedPrefix) != std::end(params))
			{
				result += params.at(collectedPrefix);
			}
			else
			{ // collected prefix is fail and probably contain search substring in itself
				reversedBufferFirst = collectedPrefix;
				std::cout << reversedBufferFirst; 
				std::reverse(std::begin(reversedBufferFirst), std::end(reversedBufferFirst));
				reversedBufferSecond = ExpandTemplate(reversedBufferFirst, newParamsForFailPrefix);
				std::cout << "-" << reversedBufferSecond << std::endl;
				std::reverse(std::begin(reversedBufferSecond), std::end(reversedBufferSecond));

				result += reversedBufferSecond;
				newParamsForFailPrefix.empty();
				std::cout << "Returned" << std::endl;
			}

			std::cout << "Result:'" << result << "'" << std::endl;
			collectedPrefix = "";
			state = &rootState;
		}
	}

	return result;
}

// else if (!state->isTerminal && !isNextStateAtSamePrefix && std::size(collectedPrefix))
