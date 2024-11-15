#include <LTEngine/text/localization.hpp>


using namespace LTEngine;
using namespace LTEngine::Text;


void Localization::addMapping(Language lang, std::string path, std::string localizedText) {
	m_textPaths[std::make_pair(lang, path)] = localizedText;
}

bool Localization::doesMappingExist(Language lang, std::string path) {
	return m_textPaths.find(std::make_pair(lang, path)) != m_textPaths.end();
}


std::string Localization::getLocalized(Language lang, std::string path) {
	return m_textPaths.at(std::make_pair(lang, path));
}
