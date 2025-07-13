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

	void add_mapping(u32 locale, std::string path, std::string localized_text);
	bool does_mapping_exist(u32 locale, std::string path);

	std::string get_localized(u32 locale, std::string path);

  private:
	std::unordered_map<std::string, std::unordered_map<u32, std::string>> _mappings;
};
} // namespace LTEngine::Text

#endif
