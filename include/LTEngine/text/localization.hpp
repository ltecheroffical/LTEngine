#ifndef _LTENGINE_LOCALIZATION_HPP_
#define _LTENGINE_LOCALIZATION_HPP_

#include <string>
#include <unordered_map>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Text {
	class Localization {
	public:
		enum class Language {
			en_US = 0,
			en_GB,
			en_CA,
			es_ES,
			es_MX,
			fr_FR,
			fr_CA,
			de_DE,
			it_IT,
			pt_PT,
			pt_BR,
			zh_CN,
			zh_TW,
			ja_JP,
			ko_KR,
			ru_RU,
			ar_SA
		};

		Localization() = default;
		~Localization() = default;

		void addMapping(Language lang, std::string path, std::string localizedText);
		bool doesMappingExist(Language lang, std::string path);

		std::string getLocalized(Language lang, std::string path);

	private:
		std::unordered_map<u32, std::string> m_textPaths;

		std::unordered_map<std::string, u32> m_pathMapping;
		std::unordered_map<u32, std::pair<Language, u32>> m_languageMapping;

		u32 m_nextLanguageId = 0;
		u32 m_nextTextId = 0;
	};
} // namespace LTEngine::Text

#endif
