#include "UrlParsingError.h"


CUrlParsingError::CUrlParsingError(std::string const & errorStr)
	: std::invalid_argument(errorStr)
{
}
