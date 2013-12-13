// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

namespace library
{
  // title_pskel
  //

  inline
  void title_pskel::
  lang_parser (::xml_schema::string_pskel& p)
  {
    this->lang_parser_ = &p;
  }

  inline
  void title_pskel::
  parsers (::xml_schema::string_pskel& lang)
  {
    this->lang_parser_ = &lang;
  }

  inline
  title_pskel::
  title_pskel ()
  : lang_parser_ (0)
  {
  }

  // person_pskel
  //

  inline
  void person_pskel::
  name_parser (::xml_schema::string_pskel& p)
  {
    this->name_parser_ = &p;
  }

  inline
  void person_pskel::
  born_parser (::xml_schema::string_pskel& p)
  {
    this->born_parser_ = &p;
  }

  inline
  void person_pskel::
  died_parser (::xml_schema::string_pskel& p)
  {
    this->died_parser_ = &p;
  }

  inline
  void person_pskel::
  parsers (::xml_schema::string_pskel& name,
           ::xml_schema::string_pskel& born,
           ::xml_schema::string_pskel& died)
  {
    this->name_parser_ = &name;
    this->born_parser_ = &born;
    this->died_parser_ = &died;
  }

  inline
  person_pskel::
  person_pskel ()
  : name_parser_ (0),
    born_parser_ (0),
    died_parser_ (0)
  {
  }

  // author_pskel
  //

  inline
  void author_pskel::
  recommends_parser (::xml_schema::idref_pskel& p)
  {
    this->recommends_parser_ = &p;
  }

  inline
  void author_pskel::
  parsers (::xml_schema::string_pskel& name,
           ::xml_schema::string_pskel& born,
           ::xml_schema::string_pskel& died,
           ::xml_schema::idref_pskel& recommends)
  {
    this->name_parser_ = &name;
    this->born_parser_ = &born;
    this->died_parser_ = &died;
    this->recommends_parser_ = &recommends;
  }

  inline
  author_pskel::
  author_pskel ()
  : recommends_parser_ (0)
  {
  }

  // book_pskel
  //

  inline
  void book_pskel::
  isbn_parser (::library::isbn_pskel& p)
  {
    this->isbn_parser_ = &p;
  }

  inline
  void book_pskel::
  title_parser (::library::title_pskel& p)
  {
    this->title_parser_ = &p;
  }

  inline
  void book_pskel::
  genre_parser (::library::genre_pskel& p)
  {
    this->genre_parser_ = &p;
  }

  inline
  void book_pskel::
  author_parser (::library::author_pskel& p)
  {
    this->author_parser_ = &p;
  }

  inline
  void book_pskel::
  available_parser (::xml_schema::boolean_pskel& p)
  {
    this->available_parser_ = &p;
  }

  inline
  void book_pskel::
  id_parser (::xml_schema::id_pskel& p)
  {
    this->id_parser_ = &p;
  }

  inline
  void book_pskel::
  parsers (::library::isbn_pskel& isbn,
           ::library::title_pskel& title,
           ::library::genre_pskel& genre,
           ::library::author_pskel& author,
           ::xml_schema::boolean_pskel& available,
           ::xml_schema::id_pskel& id)
  {
    this->isbn_parser_ = &isbn;
    this->title_parser_ = &title;
    this->genre_parser_ = &genre;
    this->author_parser_ = &author;
    this->available_parser_ = &available;
    this->id_parser_ = &id;
  }

  inline
  book_pskel::
  book_pskel ()
  : isbn_parser_ (0),
    title_parser_ (0),
    genre_parser_ (0),
    author_parser_ (0),
    available_parser_ (0),
    id_parser_ (0)
  {
  }

  // catalog_pskel
  //

  inline
  void catalog_pskel::
  book_parser (::library::book_pskel& p)
  {
    this->book_parser_ = &p;
  }

  inline
  void catalog_pskel::
  parsers (::library::book_pskel& book)
  {
    this->book_parser_ = &book;
  }

  inline
  catalog_pskel::
  catalog_pskel ()
  : book_parser_ (0)
  {
  }
}

// Begin epilogue.
//
//
// End epilogue.

