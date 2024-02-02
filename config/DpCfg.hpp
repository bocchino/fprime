// ======================================================================
// \title  DpCfg.hpp
// \author bocchino
// \brief  hpp file for data product configuration
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef DPCFG_HPP
#define DPCFG_HPP

#include "config/FpConfig.h"

// Workaround for the fact that the configurable string size is named in the prototype
// of the port invocation function. We should fix this in the C++ code generator.
#define DpWriterNotificationString Svc::DpWrittenPortStrings::StringSize256

// The format string for a file name
// The format arguments are container ID, time seconds, and time microseconds
constexpr const char *DP_FILENAME_FORMAT = "Dp_%08" PRI_FwDpIdType "_%08" PRIu32 "_%08" PRIu32 ".fdp";

#endif
