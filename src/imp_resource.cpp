/// imp_resource.cpp
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//
#include "imp_resource.h"
#include "imp_platform.h"
#include <stdexcept>

namespace impostorem
{
ImpResource::ImpResource(int resource)
    : m_resSize(0)
    , m_resPos(0)
    , m_resMem(nullptr)
{
    if(!GetResource(resource, m_resSize, m_resMem))
    {
        throw std::runtime_error("Unable to load resource!");
    }
}

ImpResource::~ImpResource() noexcept
{
    FreeResource(m_resMem);
}

uint32_t ImpResource::readRawData(int8_t* buffer, uint32_t size)
{
    if(m_resMem == nullptr)
    {
        return 0;
    }

    if(m_resPos >= m_resSize)
    {
        return 0;
    }

    size_t copyAmount = size;
    if(copyAmount > m_resSize - m_resPos)
    {
        copyAmount = m_resSize - m_resPos;
    }

    memcpy(buffer, m_resMem + m_resPos, copyAmount);
    m_resPos += copyAmount;

    return static_cast<uint32_t>(copyAmount);
}

void ImpResource::rewind()
{
    m_resPos = 0;
}
}  // namespace impostorem
