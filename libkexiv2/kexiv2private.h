/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2007-09-03
 * Description : Exiv2 library interface for KDE
 *
 * Copyright (C) 2006-2007 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2006-2007 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

 // C++ includes.

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>

// Qt includes.

#include <QFile>
#include <QImage>
#include <QSize>
#include <QTextCodec>
#include <QMatrix>
#include <QFileInfo>
#include <QDataStream>

// KDE includes.

#include <ktemporaryfile.h>
#include <kencodingdetector.h>
#include <kstringhandler.h>
#include <kdeversion.h>

// Exiv2 includes.

// The pragmas are required to be able to catch exceptions thrown by libexiv2:
// See http://gcc.gnu.org/wiki/Visibility, the section about c++ exceptions.
// They are needed for all libexiv2 versions that do not care about visibility.
#pragma GCC visibility push(default)
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <exiv2/jpgimage.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#pragma GCC visibility pop

// Check if Exiv2 support XMP

#if (EXIV2_MAJOR_VERSION ==0 && EXIV2_MINOR_VERSION ==15 && EXIV2_PATCH_VERSION >=99) || \
    (EXIV2_MAJOR_VERSION ==0 && EXIV2_MINOR_VERSION >15 ) || \
    (EXIV2_MAJOR_VERSION >0)
#   define _XMP_SUPPORT_ 1
#endif 

// Make sure an EXIV2_TEST_VERSION macro exists:

#ifdef EXIV2_VERSION
#    ifndef EXIV2_TEST_VERSION
#        define EXIV2_TEST_VERSION(major,minor,patch) \
         ( EXIV2_VERSION >= EXIV2_MAKE_VERSION(major,minor,patch) )
#    endif
#else
#    define EXIV2_TEST_VERSION(major,minor,patch) (false)
#endif

#ifndef _XMP_SUPPORT_

// Dummy redifinition of XmpData class to compile fine 
// if XMP metadata support is not available from Exiv2
namespace Exiv2
{
    class XmpData{};
}
#endif 

namespace KExiv2Iface
{

class KExiv2Priv
{
public:

    KExiv2Priv()
    {
        imageComments = std::string();
    }

    QString         filePath;

    std::string     imageComments;

    Exiv2::ExifData exifMetadata;

    Exiv2::IptcData iptcMetadata;

#ifdef _XMP_SUPPORT_
    Exiv2::XmpData  xmpMetadata;
#endif
};

}  // NameSpace KExiv2Iface