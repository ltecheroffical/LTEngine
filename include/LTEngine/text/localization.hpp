#ifndef _LTENGINE_LOCALIZATION_HPP_
#define _LTENGINE_LOCALIZATION_HPP_

#include <string>
#include <unordered_map>

#include <LTEngine/common/compiler_utils.h>

namespace LTEngine::Text {
class LTENGINE_API Localization {
  public:
	Localization() = default;
	~Localization() = default;

	void addMapping(u32 locale, std::string path, std::string localizedText);
	bool doesMappingExist(u32 locale, std::string path);

	std::string getLocalized(u32 locale, std::string path);

  private:
	std::unordered_map<std::string, std::unordered_map<u32, std::string>> m_mappings;
};
} // namespace LTEngine::Text

#endif
