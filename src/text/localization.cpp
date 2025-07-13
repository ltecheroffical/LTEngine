#include <LTEngine/text/localization.hpp>


using namespace LTEngine;
using namespace LTEngine::Text;

void Localization::addMapping(u32 locale, std::string path, std::string localizedText) {
	m_mappings[path][locale] = localizedText;
}

bool Localization::doesMappingExist(u32 locale, std::string path) {
	if (!m_mappings.contains(path)) {
		return false;
	}

	if (!m_mappings.at(path).contains(locale)) {
		return false;
	}

	return true;
}

std::string Localization::getLocalized(u32 locale, std::string path) {
	if (!doesMappingExist(locale, path)) {
		return path; // Very simple fallback, better than throwing an exception
	}

	return m_mappings[path][locale];
}
