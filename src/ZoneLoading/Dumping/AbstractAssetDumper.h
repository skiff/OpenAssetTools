#pragma once

#include "IAssetDumper.h"
#include "Utils/FileAPI.h"
#include "Utils/PathUtils.h"

#include <cstdio>

template<class T>
class AbstractAssetDumper : public IAssetDumper<T>
{
protected:
    virtual std::string GetFileNameForAsset(T* asset) = 0;
    virtual void DumpAsset(T* asset, FileAPI::File* out) = 0;

public:
    void DumpPool(AssetPool<T>* pool, const std::string& basePath) override
    {
        for(auto assetInfo : *pool)
        {
            std::string assetFilePath = utils::Path::Combine(basePath, GetFileNameForAsset(assetInfo->m_asset));

            FileAPI::DirectoryCreate(utils::Path::GetDirectory(assetFilePath));

            auto file = FileAPI::Open(assetFilePath, FileAPI::Mode::MODE_WRITE);

            if(file.IsOpen())
            {
                DumpAsset(assetInfo->m_asset, &file);

                file.Close();
            }
            else
            {
                printf("Failed to open file '%s' to dump asset '%s'\n", assetFilePath.c_str(), assetInfo->m_name.c_str());
            }
        }
    }
};