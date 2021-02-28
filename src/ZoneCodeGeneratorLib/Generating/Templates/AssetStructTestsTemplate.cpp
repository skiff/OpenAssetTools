#include "AssetStructTestsTemplate.h"

#include <iostream>
#include <sstream>

#include "Domain/Computations/StructureComputations.h"
#include "Internal/BaseTemplate.h"

class AssetStructTestsTemplate::Internal final : BaseTemplate
{
    void TestMethod(StructureInformation* structure)
    {
        LINE("TEST_CASE(\""<<m_env.m_game<<"::"<<m_env.m_asset->m_definition->GetFullName()<<": Tests for "<<structure->m_definition->GetFullName()<<"\", \"[assetstruct]\")")
        LINE("{")
        m_intendation++;
        LINE("REQUIRE("<<structure->m_definition->GetSize()<<"u == sizeof("<<structure->m_definition->GetFullName()<<"));")
        LINE("REQUIRE("<<structure->m_definition->GetAlignment()<<"u == alignof("<<structure->m_definition->GetFullName()<<"));")
        m_intendation--;
        LINE("}")
    }

public:
    Internal(std::ostream& stream, RenderingContext* context)
        : BaseTemplate(stream, context)
    {
    }

    void Source()
    {
        LINE("// ====================================================================")
        LINE("// This file has been generated by ZoneCodeGenerator.")
        LINE("// Do not modify.")
        LINE("// Any changes will be discarded when regenerating.")
        LINE("// ====================================================================")
        LINE("")
        LINE("#include <catch2/catch.hpp>")
        LINE("#include \"Game/" << m_env.m_game << "/" << m_env.m_game << ".h\"")
        LINE("")
        LINE("using namespace " << m_env.m_game << ";")
        LINE("")
        LINE("namespace game::"<<m_env.m_game<<"::xassets::asset_"<<Lower(m_env.m_asset->m_definition->m_name))
        LINE("{")
        m_intendation++;

        TestMethod(m_env.m_asset);
        for (auto* structure : m_env.m_used_structures)
        {
            StructureComputations computations(structure->m_info);
            if (!structure->m_info->m_definition->m_anonymous && !computations.IsAsset())
                TestMethod(structure->m_info);
        }

        m_intendation--;
        LINE("}")
    }
};

std::vector<CodeTemplateFile> AssetStructTestsTemplate::GetFilesToRender(RenderingContext* context)
{
    std::vector<CodeTemplateFile> files;

    auto assetName = context->m_asset->m_definition->m_name;
    for (auto& c : assetName)
        c = static_cast<char>(tolower(c));

    {
        std::ostringstream str;
        str << assetName << '/' << assetName << "_struct_test.cpp";
        files.emplace_back(str.str(), TAG_SOURCE);
    }

    return files;
}

void AssetStructTestsTemplate::RenderFile(std::ostream& stream, const int fileTag, RenderingContext* context)
{
    Internal internal(stream, context);

    if (fileTag == TAG_SOURCE)
        internal.Source();
    else
        std::cout << "Invalid tag in AssetStructTestsTemplate\n";
}