/// imp_resource.h
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "vstgui/uidescription/icontentprovider.h"
#include "vstgui/uidescription/uidescription.h"

namespace impostorem
{
/// Simple Embedded resource handler for VST3
/// Allows serial reading of Windows binary resources
class ImpResource : public VSTGUI::IContentProvider
{
public:
    /// ImpResource constructor from a resource ID
    /// \param resource - Resource ID, e.g. IDR_UIDESC1
    ImpResource(int resource);
    virtual ~ImpResource() noexcept;

    /// Override to read bytes out of the resource
    /// \param buffer - output buffer
    /// \param size - size to read
    /// \return uint32_t - amount actually read
    uint32_t readRawData(int8_t* buffer, uint32_t size) override;

    /// rewind() resets the beginning of resource
    void rewind() override;

protected:
    size_t  m_resSize;  ///< Size of resource in bytes
    size_t  m_resPos;   ///< Current read position
    int8_t* m_resMem;   ///< Pointer to resource memory
};

}  // namespace impostorem