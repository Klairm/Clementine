/* This file is part of Clementine.

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef M3UPARSER_H
#define M3UPARSER_H

#include <QUrl>

#include "gtest/gtest_prod.h"

#include "parserbase.h"

class M3UParser : public ParserBase {
  Q_OBJECT

 public:
  M3UParser(QObject* parent = 0);

  QString name() const { return "M3U"; }
  QStringList file_extensions() const { return QStringList() << "m3u"; }
  QString mime_type() const { return "text/uri-list"; }

  bool TryMagic(const QByteArray &data) const;

  SongList Load(QIODevice* device, const QDir& dir = QDir()) const;
  void Save(const SongList &songs, QIODevice* device, const QDir& dir = QDir()) const;

 private:
  enum M3UType {
    STANDARD = 0,
    EXTENDED,  // Includes extended info (track, artist, etc.)
    LINK,      // Points to a directory.
  };

  struct Metadata {
    Metadata() : length(-1) {}
    QString artist;
    QString title;
    int length;
  };

  bool ParseMetadata(const QString& line, Metadata* metadata) const;

  FRIEND_TEST(M3UParserTest, ParsesMetadata);
  FRIEND_TEST(M3UParserTest, ParsesTrackLocation);
  FRIEND_TEST(M3UParserTest, ParsesTrackLocationRelative);
  FRIEND_TEST(M3UParserTest, ParsesTrackLocationHttp);
#ifdef Q_OS_WIN32
  FRIEND_TEST(M3UParserTest, ParsesTrackLocationAbsoluteWindows);
#endif  // Q_OS_WIN32
};

#endif  // M3UPARSER_H
