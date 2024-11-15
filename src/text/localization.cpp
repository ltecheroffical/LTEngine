#include <LTEngine/text/localization.hpp>


using namespace LTEngine;
using namespace LTEngine::Text;


void Localization::addMapping(Language lang, std::string path, std::string localizedText) {
	u32 textId = m_nextTextId++;
	u32 langId = m_nextLanguageId++;

	m_pathMapping[path] = langId;
	m_languageMapping[langId] = std::make_pair(lang, textId);
	m_textPaths[textId] = localizedText;
}

bool Localization::doesMappingExist(Language lang, std::string path) {
	if (!m_pathMapping.contains(path)) { return false; }
	u32 textId = m_pathMapping.at(path);
	if (!m_languageMapping.contains(textId)) { return false; }
	return m_languageMapping.at(textId).first == lang;
}


std::string Localization::getLocalized(Language lang, std::string path) {
	if (!doesMappingExist(lang, path)) {
		return path; // Very simple fallback, better than throwing an exception
	}

	u32 textId = m_pathMapping.at(path);
	return m_textPaths.at(textId);
}
