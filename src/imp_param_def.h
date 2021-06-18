/// imp_param_def.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include <cstdint>
#include <string>

namespace impostorem
{
/// Parameter ID - to identify parameters to hosts
typedef int32_t ImpParamId;

/// Type of parameter (floating point, integer)
enum class ImpParamType : int32_t
{
    kFloat = 0,  ///< Floating point parameter
    kInt32       ///< Integer parameter
};

/// ImpParamDef - Parameter Definition structure
/// This is to allow ImpParams to be defined in a nice table for a plugin
class ImpParamDef
{
public:
    /// ImpParamDef constructor
    /// \param name - parameter name (may NOT be null - use empty string)
    /// \param units - units for the value (may NOT be null - use empty string)
    /// \param id - parameter id
    /// \param paramType - type of parameter (kFloat or kInt32)
    /// \param step - step size for parameter (between values)
    /// \param minVal - minimum parameter value
    /// \param maxVal - maximum parameter value
    /// \param defVal - default value for the parameter
    ImpParamDef(const wchar_t* name,
                const wchar_t* units,
                ImpParamId     id,
                ImpParamType   paramType,
                float          step,
                float          minVal,
                float          maxVal,
                float          defVal);

    virtual ~ImpParamDef() = default;

    /// Retrieve the parameter name
    const std::wstring& name() const;

    /// Retrieve the parameter's units (or empty string)
    const std::wstring& units() const;

    /// Retrieve the parameter id
    ImpParamId id() const;

    /// Retrieve the parameter type
    ImpParamType type() const;

    /// Retrieve the numeric range (maxVal - minVal)
    /// \return float - distance from min to max value
    float range() const;

    /// Retrieve the number of steps from min to max
    /// \return int - number of steps for value
    int numSteps() const;

    /// Retrieve the normalized step size
    /// \return float Normalized step size for the parameter
    float getNormalStepSize() const;

    /// Retrieve the normalized default value
    /// \return float normalized default value
    float getNormalDefVal() const;

    /// Retrieve the normalized value
    ///       (value - minVal)/range
    /// \param value value to normalize
    /// \return float normalized value
    float normalize(float value) const;

    /// Retrieve the denormalized value
    ///       range * value + minVal
    /// \param value value to denormalize
    /// \return float denormalized value
    float denormalize(float value) const;

    /// Convert a wide string to value
    /// \param valStr - wide string representing value to convert
    /// \return float - normalized value out
    virtual float fromString(const std::wstring& valStr) const;

    /// Convert a value to a wide string
    /// \param normVal - normalized value to convert
    /// \return std::wstring - wide string representing value
    virtual std::wstring toString(float normVal) const;

protected:
    const std::wstring m_name;       ///< Parameter Name
    const std::wstring m_units;      ///< Parameter Units
    const ImpParamId   m_id;         ///< Parameter ID
    const ImpParamType m_paramType;  ///< Type (kFloat/kInt32)
    const float        m_step;       ///< Step size when inc/decrementing value
    const float        m_minVal;     ///< Minimum param value
    const float        m_maxVal;     ///< Maximum param value
    const float        m_defVal;     ///< Default param value
};

/// ImpParamDefMod - modifier params.
/// These are parameters that modify a value, but leave it alone if the parameter
/// is set to denormalized 0.
///
/// For example, Channel parameters interpret 0 as "don't touch the channel"
/// All other values specify the output channel to translate to.
///
/// Right now, mostly just for "Unchanged" string at 0
class ImpParamDefMod : public ImpParamDef
{
public:
    ImpParamDefMod(const wchar_t* name,
                   const wchar_t* units,
                   ImpParamId     id,
                   ImpParamType   paramType,
                   float          step,
                   float          minVal,
                   float          maxVal,
                   float          defVal);

    ~ImpParamDefMod() override = default;

    /// fromString override - interprets "Unchanged" as 0.
    /// \param valStr - string to interpret
    /// \param float - normalized value from string
    float fromString(const std::wstring& valStr) const override;

    /// toString override - returns "Unchanged" for 0 value.
    /// \param normVal - normalized value to convert to a string
    /// \return std::wstring - string value for the channel, "Unchanged" for 0.
    std::wstring toString(float normVal) const override;
};

}  // namespace impostorem
