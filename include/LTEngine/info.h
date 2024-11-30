#include <LTEngine/common/types/inttypes.h>


#ifndef _LTENGINE_INFO_HPP_
#define _LTENGINE_INFO_HPP_

inline const LTEngine_u32 LTEngine_Version[3] = {0, 9, 8};
inline const char *LTEngine_VersionText = "Beta v0.9.8";
inline const char *LTEngine_License = "MIT";
inline const char *LTEngine_Website = "https://github.com/ltecherofficial/LTEngine";

#ifdef __cplusplus
namespace LTEngine {
	inline const u32 LTEngine_Version[3] = {LTEngine_Version[0], LTEngine_Version[1], LTEngine_Version[2]};
	inline const char *LTEngine_VersionText = LTEngine_VersionText;
	inline const char *LTEngine_License = LTEngine_License;
	inline const char *LTEngine_Website = LTEngine_Website;
} // namespace LTEngine
#endif

#endif
