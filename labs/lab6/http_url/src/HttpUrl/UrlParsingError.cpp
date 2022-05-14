#include "../../headers/HttpUrl/CUrlParsingError.h"

UrlParsingError::UrlParsingError(const char* msg)
	: std::invalid_argument(msg)
{
}
