#ifndef _LTENGINE_ASSET_POST_PROCESSOR_HPP_
#define _LTENGINE_ASSET_POST_PROCESSOR_HPP_

#include <vector>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
	/**
	 * @brief Processes assets before saving and loading and handles asset load failures.
	 *
	 * @details
	 * The post processor processes assets before saving and loading and handles load failures.
	 * This can be used in multiple ways, some examples are:
	 *  - Compression
	 *  - Encryption
	 *  - Downloading from server
	 *  - Pretending assets that don't exist, exist without modifying the assets
	 *
	 * This is very useful for large games, times when the dev doesn't want users to access the asset,
	 * and live service games.
	 */
	class AssetManagerPostProcessor {
	public:
		virtual ~AssetManagerPostProcessor() = 0;

		/**
		 * @brief Process asset before it is saved.
		 *
		 * @param data The data of the asset as a pointer.
		 */
		virtual void postProcess(std::string path, std::vector<u8> *data) = 0;
		/**
		 * @brief Process asset before it is given to the user.
		 *
		 * @param data The data of the asset as a pointer.
		 */
		virtual void preProcess(std::string path, std::vector<u8> *data) = 0;

		/**
		 * @brief Handle if loading an asset failed.
		 *
		 * @param data The data of the asset as a pointer.
		 * @returns If the asset loading should continue with the current data. If this is false, an exception will be thrown.
		 */
		virtual bool assetLoadFailed(std::string path, std::vector<u8> *data) { return false; }
	};
} // namespace LTEngine

#endif
