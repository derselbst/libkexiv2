/* ============================================================
 * Authors: Gilles Caulier <caulier dot gilles at kdemail dot net>
 *          Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Date   : 2006-09-15
 * Description : Exiv2 library interface
 *
 * Copyright 2006-2007 by Gilles Caulier and Marcel Wiesweg
 *
 * NOTE: This class is a simplified version of Digikam::DMetadata
 *       class from digiKam core. Please contact digiKam team 
 *       before to change/fix/improve this implementation.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef LIB_KEXIV2_H
#define LIB_KEXIV2_H

// C++ includes.

#include <string>

// QT includes.

#include <qcstring.h>
#include <qstring.h>
#include <qimage.h>
#include <qdatetime.h>

// Local includes.

#include "libkexiv2_export.h"

namespace Exiv2
{
    class Exifdatum;
}

namespace KExiv2Library
{

class LibKExiv2Priv;

class LIBKEXIV2_EXPORT LibKExiv2
{

public:

    enum ImageOrientation
    {
        ORIENTATION_UNSPECIFIED  = 0, 
        ORIENTATION_NORMAL       = 1, 
        ORIENTATION_HFLIP        = 2, 
        ORIENTATION_ROT_180      = 3, 
        ORIENTATION_VFLIP        = 4, 
        ORIENTATION_ROT_90_HFLIP = 5, 
        ORIENTATION_ROT_90       = 6, 
        ORIENTATION_ROT_90_VFLIP = 7, 
        ORIENTATION_ROT_270      = 8
    };

public:

    LibKExiv2();
    ~LibKExiv2();
    
    bool load(const QString& filePath);
    bool save(const QString& filePath);

    QByteArray getComments() const;
    QByteArray getExif() const;
    QByteArray getIptc(bool addIrbHeader=false) const;

    bool setComments(const QByteArray& data);
    bool setExif(const QByteArray& data);
    bool setIptc(const QByteArray& data);

    bool clearExif();
    bool clearIptc();

    bool setImageProgramId(const QString& program, const QString& version);
    bool setImageDimensions(const QSize& size);
    bool setExifThumbnail(const QImage& thumb);
    bool setImagePreview(const QImage& preview);
    bool setImageOrientation(ImageOrientation orientation);

    QStringList getImageKeywords() const;
    bool setImageKeywords(const QStringList& oldKeywords, const QStringList& newKeywords);

    QStringList getImageSubjects() const;
    bool setImageSubjects(const QStringList& oldSubjects, const QStringList& newSubjects);

    QStringList getImageSubCategories() const;
    bool setImageSubCategories(const QStringList& oldSubCategories, const QStringList& newSubCategories);

    bool setGPSInfo(double altitude, double latitude, double longitude);
    bool getGPSInfo(double& altitude, double& latitude, double& longitude);
    bool removeGPSInfo();

    QString getExifComment() const;
    bool    setExifComment(const QString& comment);

    QString    getExifTagString(const char *exifTagName, bool escapeCR=true) const;
    QByteArray getExifTagData(const char *exifTagName) const;
    bool       getExifTagLong(const char* exifTagName, long &val);
    bool       getExifTagRational(const char *exifTagName, long int &num, long int &den, int component=0);
    QString    getIptcTagString(const char* iptcTagName, bool escapeCR=true) const;
    QByteArray getIptcTagData(const char *iptcTagName) const;

    bool setExifTagString(const char *exifTagName, const QString& value);
    bool setExifTagLong(const char *exifTagName, long val);
    bool setExifTagRational(const char *exifTagName, long int num, long int den);
    bool setIptcTagString(const char *iptcTagName, const QString& value);

    bool removeExifTag(const char *exifTagName);
    bool removeIptcTag(const char *iptcTagName);

    LibKExiv2::ImageOrientation getImageOrientation();
    QDateTime getImageDateTime() const;

    static bool isReadOnly(const QString& filePath);
    static QString convertCommentValue(const Exiv2::Exifdatum &comment);
    static QString detectEncodingAndDecode(const std::string &value);
    static void convertToRational(double number, long int* numerator, 
                                  long int* denominator, int rounding);

private:

    LibKExiv2Priv *d;
};

}  // NameSpace KExiv2Library

#endif /* LIB_KEXIV2_H */
