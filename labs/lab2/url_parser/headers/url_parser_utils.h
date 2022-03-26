#pragma once

bool AreMatchesCorrect(const std::smatch& matches);
std::regex GetRegExOfUrl();
std::optional<int> ParsePortAccordingProtocol(const std::string& match, const Protocol& protocol);
std::optional<Protocol> ParseProtocol(const std::string& protocol);
bool StringEqualsInsensetive(const std::string& a, const std::string& b);
