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

#ifndef INPUT_CUBOIDS_HXX
#define INPUT_CUBOIDS_HXX

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3030000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::auto_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
class ori_t;
class startV_t;
class size3D_t;
class cuboid_t;
class cuboids_t;

#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class ori_t: public ::xml_schema::type
{
  public:
  // oriX
  // 
  typedef ::xml_schema::decimal oriX_type;
  typedef ::xsd::cxx::tree::traits< oriX_type, char, ::xsd::cxx::tree::schema_type::decimal > oriX_traits;

  const oriX_type&
  oriX () const;

  oriX_type&
  oriX ();

  void
  oriX (const oriX_type& x);

  // oriY
  // 
  typedef ::xml_schema::decimal oriY_type;
  typedef ::xsd::cxx::tree::traits< oriY_type, char, ::xsd::cxx::tree::schema_type::decimal > oriY_traits;

  const oriY_type&
  oriY () const;

  oriY_type&
  oriY ();

  void
  oriY (const oriY_type& x);

  // oriZ
  // 
  typedef ::xml_schema::decimal oriZ_type;
  typedef ::xsd::cxx::tree::traits< oriZ_type, char, ::xsd::cxx::tree::schema_type::decimal > oriZ_traits;

  const oriZ_type&
  oriZ () const;

  oriZ_type&
  oriZ ();

  void
  oriZ (const oriZ_type& x);

  // Constructors.
  //
  ori_t (const oriX_type&,
         const oriY_type&,
         const oriZ_type&);

  ori_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f = 0,
         ::xml_schema::container* c = 0);

  ori_t (const ori_t& x,
         ::xml_schema::flags f = 0,
         ::xml_schema::container* c = 0);

  virtual ori_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~ori_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< oriX_type > oriX_;
  ::xsd::cxx::tree::one< oriY_type > oriY_;
  ::xsd::cxx::tree::one< oriZ_type > oriZ_;
};

class startV_t: public ::xml_schema::type
{
  public:
  // velX
  // 
  typedef ::xml_schema::decimal velX_type;
  typedef ::xsd::cxx::tree::traits< velX_type, char, ::xsd::cxx::tree::schema_type::decimal > velX_traits;

  const velX_type&
  velX () const;

  velX_type&
  velX ();

  void
  velX (const velX_type& x);

  // velY
  // 
  typedef ::xml_schema::decimal velY_type;
  typedef ::xsd::cxx::tree::traits< velY_type, char, ::xsd::cxx::tree::schema_type::decimal > velY_traits;

  const velY_type&
  velY () const;

  velY_type&
  velY ();

  void
  velY (const velY_type& x);

  // velZ
  // 
  typedef ::xml_schema::decimal velZ_type;
  typedef ::xsd::cxx::tree::traits< velZ_type, char, ::xsd::cxx::tree::schema_type::decimal > velZ_traits;

  const velZ_type&
  velZ () const;

  velZ_type&
  velZ ();

  void
  velZ (const velZ_type& x);

  // Constructors.
  //
  startV_t (const velX_type&,
            const velY_type&,
            const velZ_type&);

  startV_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  startV_t (const startV_t& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual startV_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~startV_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< velX_type > velX_;
  ::xsd::cxx::tree::one< velY_type > velY_;
  ::xsd::cxx::tree::one< velZ_type > velZ_;
};

class size3D_t: public ::xml_schema::type
{
  public:
  // width
  // 
  typedef ::xml_schema::int_ width_type;
  typedef ::xsd::cxx::tree::traits< width_type, char > width_traits;

  const width_type&
  width () const;

  width_type&
  width ();

  void
  width (const width_type& x);

  // height
  // 
  typedef ::xml_schema::int_ height_type;
  typedef ::xsd::cxx::tree::traits< height_type, char > height_traits;

  const height_type&
  height () const;

  height_type&
  height ();

  void
  height (const height_type& x);

  // depth
  // 
  typedef ::xml_schema::int_ depth_type;
  typedef ::xsd::cxx::tree::traits< depth_type, char > depth_traits;

  const depth_type&
  depth () const;

  depth_type&
  depth ();

  void
  depth (const depth_type& x);

  // Constructors.
  //
  size3D_t (const width_type&,
            const height_type&,
            const depth_type&);

  size3D_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  size3D_t (const size3D_t& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual size3D_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~size3D_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< width_type > width_;
  ::xsd::cxx::tree::one< height_type > height_;
  ::xsd::cxx::tree::one< depth_type > depth_;
};

class cuboid_t: public ::xml_schema::type
{
  public:
  // meshWidth
  // 
  typedef ::xml_schema::decimal meshWidth_type;
  typedef ::xsd::cxx::tree::traits< meshWidth_type, char, ::xsd::cxx::tree::schema_type::decimal > meshWidth_traits;

  const meshWidth_type&
  meshWidth () const;

  meshWidth_type&
  meshWidth ();

  void
  meshWidth (const meshWidth_type& x);

  // mass
  // 
  typedef ::xml_schema::decimal mass_type;
  typedef ::xsd::cxx::tree::traits< mass_type, char, ::xsd::cxx::tree::schema_type::decimal > mass_traits;

  const mass_type&
  mass () const;

  mass_type&
  mass ();

  void
  mass (const mass_type& x);

  // meanV
  // 
  typedef ::xml_schema::decimal meanV_type;
  typedef ::xsd::cxx::tree::traits< meanV_type, char, ::xsd::cxx::tree::schema_type::decimal > meanV_traits;

  const meanV_type&
  meanV () const;

  meanV_type&
  meanV ();

  void
  meanV (const meanV_type& x);

  // parTypeC
  // 
  typedef ::xml_schema::int_ parTypeC_type;
  typedef ::xsd::cxx::tree::traits< parTypeC_type, char > parTypeC_traits;

  const parTypeC_type&
  parTypeC () const;

  parTypeC_type&
  parTypeC ();

  void
  parTypeC (const parTypeC_type& x);

  // epsilon
  // 
  typedef ::xml_schema::decimal epsilon_type;
  typedef ::xsd::cxx::tree::traits< epsilon_type, char, ::xsd::cxx::tree::schema_type::decimal > epsilon_traits;

  const epsilon_type&
  epsilon () const;

  epsilon_type&
  epsilon ();

  void
  epsilon (const epsilon_type& x);

  // sigma
  // 
  typedef ::xml_schema::decimal sigma_type;
  typedef ::xsd::cxx::tree::traits< sigma_type, char, ::xsd::cxx::tree::schema_type::decimal > sigma_traits;

  const sigma_type&
  sigma () const;

  sigma_type&
  sigma ();

  void
  sigma (const sigma_type& x);

  // originVector
  // 
  typedef ::ori_t originVector_type;
  typedef ::xsd::cxx::tree::traits< originVector_type, char > originVector_traits;

  const originVector_type&
  originVector () const;

  originVector_type&
  originVector ();

  void
  originVector (const originVector_type& x);

  void
  originVector (::std::auto_ptr< originVector_type > p);

  // startVelocity
  // 
  typedef ::startV_t startVelocity_type;
  typedef ::xsd::cxx::tree::traits< startVelocity_type, char > startVelocity_traits;

  const startVelocity_type&
  startVelocity () const;

  startVelocity_type&
  startVelocity ();

  void
  startVelocity (const startVelocity_type& x);

  void
  startVelocity (::std::auto_ptr< startVelocity_type > p);

  // size3D
  // 
  typedef ::size3D_t size3D_type;
  typedef ::xsd::cxx::tree::traits< size3D_type, char > size3D_traits;

  const size3D_type&
  size3D () const;

  size3D_type&
  size3D ();

  void
  size3D (const size3D_type& x);

  void
  size3D (::std::auto_ptr< size3D_type > p);

  // Constructors.
  //
  cuboid_t (const meshWidth_type&,
            const mass_type&,
            const meanV_type&,
            const parTypeC_type&,
            const epsilon_type&,
            const sigma_type&,
            const originVector_type&,
            const startVelocity_type&,
            const size3D_type&);

  cuboid_t (const meshWidth_type&,
            const mass_type&,
            const meanV_type&,
            const parTypeC_type&,
            const epsilon_type&,
            const sigma_type&,
            ::std::auto_ptr< originVector_type >&,
            ::std::auto_ptr< startVelocity_type >&,
            ::std::auto_ptr< size3D_type >&);

  cuboid_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  cuboid_t (const cuboid_t& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual cuboid_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~cuboid_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< meshWidth_type > meshWidth_;
  ::xsd::cxx::tree::one< mass_type > mass_;
  ::xsd::cxx::tree::one< meanV_type > meanV_;
  ::xsd::cxx::tree::one< parTypeC_type > parTypeC_;
  ::xsd::cxx::tree::one< epsilon_type > epsilon_;
  ::xsd::cxx::tree::one< sigma_type > sigma_;
  ::xsd::cxx::tree::one< originVector_type > originVector_;
  ::xsd::cxx::tree::one< startVelocity_type > startVelocity_;
  ::xsd::cxx::tree::one< size3D_type > size3D_;
};

class cuboids_t: public ::xml_schema::type
{
  public:
  // cuboid
  // 
  typedef ::cuboid_t cuboid_type;
  typedef ::xsd::cxx::tree::sequence< cuboid_type > cuboid_sequence;
  typedef cuboid_sequence::iterator cuboid_iterator;
  typedef cuboid_sequence::const_iterator cuboid_const_iterator;
  typedef ::xsd::cxx::tree::traits< cuboid_type, char > cuboid_traits;

  const cuboid_sequence&
  cuboid () const;

  cuboid_sequence&
  cuboid ();

  void
  cuboid (const cuboid_sequence& s);

  // Constructors.
  //
  cuboids_t ();

  cuboids_t (const ::xercesc::DOMElement& e,
             ::xml_schema::flags f = 0,
             ::xml_schema::container* c = 0);

  cuboids_t (const cuboids_t& x,
             ::xml_schema::flags f = 0,
             ::xml_schema::container* c = 0);

  virtual cuboids_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~cuboids_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  cuboid_sequence cuboid_;
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

// Parse a URI or a local file.
//

::std::auto_ptr< ::cuboids_t >
cuboids (const ::std::string& uri,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (const ::std::string& uri,
         ::xml_schema::error_handler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (const ::std::string& uri,
         ::xercesc::DOMErrorHandler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse std::istream.
//

::std::auto_ptr< ::cuboids_t >
cuboids (::std::istream& is,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::std::istream& is,
         ::xml_schema::error_handler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::std::istream& is,
         ::xercesc::DOMErrorHandler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::std::istream& is,
         const ::std::string& id,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::std::istream& is,
         const ::std::string& id,
         ::xml_schema::error_handler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::std::istream& is,
         const ::std::string& id,
         ::xercesc::DOMErrorHandler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::InputSource.
//

::std::auto_ptr< ::cuboids_t >
cuboids (::xercesc::InputSource& is,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::xercesc::InputSource& is,
         ::xml_schema::error_handler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::xercesc::InputSource& is,
         ::xercesc::DOMErrorHandler& eh,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::DOMDocument.
//

::std::auto_ptr< ::cuboids_t >
cuboids (const ::xercesc::DOMDocument& d,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::cuboids_t >
cuboids (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
         ::xml_schema::flags f = 0,
         const ::xml_schema::properties& p = ::xml_schema::properties ());

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // INPUT_CUBOIDS_HXX
