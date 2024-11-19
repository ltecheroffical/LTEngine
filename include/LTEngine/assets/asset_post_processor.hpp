#ifndef _LTENGINE_ASSET_POST_PROCESSOR_HPP_
#define _LTENGINE_ASSET_POST_PROCESSOR_HPP_

#include <vector>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
	class AssetManagerPostProcessor {
	public:
		virtual ~AssetManagerPostProcessor() = 0;

		virtual void preProcess(std::string path, std::vector<u8> &data) = 0;
		virtual void postProcess(std::string path, std::vector<u8> &data) = 0;

		virtual bool assetLoadFailed(std::string path, std::vector<u8> *data) { return false; }
	};
} // namespace LTEngine

#endif
