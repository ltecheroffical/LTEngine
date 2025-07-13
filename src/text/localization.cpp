#include <LTEngine/text/localization.hpp>


using namespace LTEngine;
using namespace LTEngine::Text;

void Localization::add_mapping(u32 locale, std::string path, std::string localized_text) {
	_mappings[path][locale] = localized_text;
}

bool Localization::does_mapping_exist(u32 locale, std::string path) {
	if (!_mappings.contains(path)) {
		return false;
	}

	if (!_mappings.at(path).contains(locale)) {
		return false;
	}

	return true;
}

std::string Localization::get_localized(u32 locale, std::string path) {
	if (!does_mapping_exist(locale, path)) {
		return path; // Very simple fallback, better than throwing an exception
	}

	return _mappings[path][locale];
}
