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

#ifndef INPUT_SETTING_HXX
#define INPUT_SETTING_HXX

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
class ljf_t;
class lc_t;
class domainsize_t;
class condition_t;
class inputfile_t;
class type_t;
class outputfile_t;
class pse_t;

#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class ljf_t: public ::xml_schema::type
{
  public:
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

  // Constructors.
  //
  ljf_t (const epsilon_type&,
         const sigma_type&);

  ljf_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f = 0,
         ::xml_schema::container* c = 0);

  ljf_t (const ljf_t& x,
         ::xml_schema::flags f = 0,
         ::xml_schema::container* c = 0);

  virtual ljf_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~ljf_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< epsilon_type > epsilon_;
  ::xsd::cxx::tree::one< sigma_type > sigma_;
};

class lc_t: public ::xml_schema::type
{
  public:
  // domainsize
  // 
  typedef ::domainsize_t domainsize_type;
  typedef ::xsd::cxx::tree::traits< domainsize_type, char > domainsize_traits;

  const domainsize_type&
  domainsize () const;

  domainsize_type&
  domainsize ();

  void
  domainsize (const domainsize_type& x);

  void
  domainsize (::std::auto_ptr< domainsize_type > p);

  // rcutoff
  // 
  typedef ::xml_schema::decimal rcutoff_type;
  typedef ::xsd::cxx::tree::traits< rcutoff_type, char, ::xsd::cxx::tree::schema_type::decimal > rcutoff_traits;

  const rcutoff_type&
  rcutoff () const;

  rcutoff_type&
  rcutoff ();

  void
  rcutoff (const rcutoff_type& x);

  // condition
  // 
  typedef ::condition_t condition_type;
  typedef ::xsd::cxx::tree::sequence< condition_type > condition_sequence;
  typedef condition_sequence::iterator condition_iterator;
  typedef condition_sequence::const_iterator condition_const_iterator;
  typedef ::xsd::cxx::tree::traits< condition_type, char > condition_traits;

  const condition_sequence&
  condition () const;

  condition_sequence&
  condition ();

  void
  condition (const condition_sequence& s);

  // Constructors.
  //
  lc_t (const domainsize_type&,
        const rcutoff_type&);

  lc_t (::std::auto_ptr< domainsize_type >&,
        const rcutoff_type&);

  lc_t (const ::xercesc::DOMElement& e,
        ::xml_schema::flags f = 0,
        ::xml_schema::container* c = 0);

  lc_t (const lc_t& x,
        ::xml_schema::flags f = 0,
        ::xml_schema::container* c = 0);

  virtual lc_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~lc_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< domainsize_type > domainsize_;
  ::xsd::cxx::tree::one< rcutoff_type > rcutoff_;
  condition_sequence condition_;
};

class domainsize_t: public ::xml_schema::type
{
  public:
  // domainX
  // 
  typedef ::xml_schema::decimal domainX_type;
  typedef ::xsd::cxx::tree::traits< domainX_type, char, ::xsd::cxx::tree::schema_type::decimal > domainX_traits;

  const domainX_type&
  domainX () const;

  domainX_type&
  domainX ();

  void
  domainX (const domainX_type& x);

  // domainY
  // 
  typedef ::xml_schema::decimal domainY_type;
  typedef ::xsd::cxx::tree::traits< domainY_type, char, ::xsd::cxx::tree::schema_type::decimal > domainY_traits;

  const domainY_type&
  domainY () const;

  domainY_type&
  domainY ();

  void
  domainY (const domainY_type& x);

  // domainZ
  // 
  typedef ::xml_schema::decimal domainZ_type;
  typedef ::xsd::cxx::tree::traits< domainZ_type, char, ::xsd::cxx::tree::schema_type::decimal > domainZ_traits;

  const domainZ_type&
  domainZ () const;

  domainZ_type&
  domainZ ();

  void
  domainZ (const domainZ_type& x);

  // Constructors.
  //
  domainsize_t (const domainX_type&,
                const domainY_type&,
                const domainZ_type&);

  domainsize_t (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  domainsize_t (const domainsize_t& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual domainsize_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~domainsize_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< domainX_type > domainX_;
  ::xsd::cxx::tree::one< domainY_type > domainY_;
  ::xsd::cxx::tree::one< domainZ_type > domainZ_;
};

class condition_t: public ::xsd::cxx::tree::fundamental_base< ::xml_schema::int_, char, ::xml_schema::simple_type >
{
  public:
  condition_t (::xml_schema::int_ v);

  condition_t (const ::xercesc::DOMElement& e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  condition_t (const ::xercesc::DOMAttr& a,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  condition_t (const ::std::string& s,
               const ::xercesc::DOMElement* e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  condition_t (const condition_t& x,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  virtual condition_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;
};

class inputfile_t: public ::xml_schema::type
{
  public:
  // name
  // 
  typedef ::xml_schema::string name_type;
  typedef ::xsd::cxx::tree::traits< name_type, char > name_traits;

  const name_type&
  name () const;

  name_type&
  name ();

  void
  name (const name_type& x);

  void
  name (::std::auto_ptr< name_type > p);

  // type
  // 
  typedef ::type_t type_type;
  typedef ::xsd::cxx::tree::traits< type_type, char > type_traits;

  const type_type&
  type () const;

  type_type&
  type ();

  void
  type (const type_type& x);

  void
  type (::std::auto_ptr< type_type > p);

  // Constructors.
  //
  inputfile_t (const name_type&,
               const type_type&);

  inputfile_t (const ::xercesc::DOMElement& e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  inputfile_t (const inputfile_t& x,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  virtual inputfile_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~inputfile_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< name_type > name_;
  ::xsd::cxx::tree::one< type_type > type_;
};

class type_t: public ::xml_schema::string
{
  public:
  enum value
  {
    cuboids,
    particles,
    spheres
  };

  type_t (value v);

  type_t (const char* v);

  type_t (const ::std::string& v);

  type_t (const ::xml_schema::string& v);

  type_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  type_t (const ::xercesc::DOMAttr& a,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  type_t (const ::std::string& s,
          const ::xercesc::DOMElement* e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  type_t (const type_t& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  virtual type_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  type_t&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_type_t_convert ();
  }

  protected:
  value
  _xsd_type_t_convert () const;

  public:
  static const char* const _xsd_type_t_literals_[3];
  static const value _xsd_type_t_indexes_[3];
};

class outputfile_t: public ::xml_schema::type
{
  public:
  // name
  // 
  typedef ::xml_schema::string name_type;
  typedef ::xsd::cxx::tree::traits< name_type, char > name_traits;

  const name_type&
  name () const;

  name_type&
  name ();

  void
  name (const name_type& x);

  void
  name (::std::auto_ptr< name_type > p);

  // freq
  // 
  typedef ::xml_schema::short_ freq_type;
  typedef ::xsd::cxx::tree::traits< freq_type, char > freq_traits;

  const freq_type&
  freq () const;

  freq_type&
  freq ();

  void
  freq (const freq_type& x);

  // Constructors.
  //
  outputfile_t (const name_type&,
                const freq_type&);

  outputfile_t (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  outputfile_t (const outputfile_t& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual outputfile_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~outputfile_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< name_type > name_;
  ::xsd::cxx::tree::one< freq_type > freq_;
};

class pse_t: public ::xml_schema::type
{
  public:
  // start_time
  // 
  typedef ::xml_schema::decimal start_time_type;
  typedef ::xsd::cxx::tree::traits< start_time_type, char, ::xsd::cxx::tree::schema_type::decimal > start_time_traits;

  const start_time_type&
  start_time () const;

  start_time_type&
  start_time ();

  void
  start_time (const start_time_type& x);

  // t_end
  // 
  typedef ::xml_schema::decimal t_end_type;
  typedef ::xsd::cxx::tree::traits< t_end_type, char, ::xsd::cxx::tree::schema_type::decimal > t_end_traits;

  const t_end_type&
  t_end () const;

  t_end_type&
  t_end ();

  void
  t_end (const t_end_type& x);

  // delta_t
  // 
  typedef ::xml_schema::decimal delta_t_type;
  typedef ::xsd::cxx::tree::traits< delta_t_type, char, ::xsd::cxx::tree::schema_type::decimal > delta_t_traits;

  const delta_t_type&
  delta_t () const;

  delta_t_type&
  delta_t ();

  void
  delta_t (const delta_t_type& x);

  // ljf
  // 
  typedef ::ljf_t ljf_type;
  typedef ::xsd::cxx::tree::traits< ljf_type, char > ljf_traits;

  const ljf_type&
  ljf () const;

  ljf_type&
  ljf ();

  void
  ljf (const ljf_type& x);

  void
  ljf (::std::auto_ptr< ljf_type > p);

  // lc
  // 
  typedef ::lc_t lc_type;
  typedef ::xsd::cxx::tree::traits< lc_type, char > lc_traits;

  const lc_type&
  lc () const;

  lc_type&
  lc ();

  void
  lc (const lc_type& x);

  void
  lc (::std::auto_ptr< lc_type > p);

  // inputfile
  // 
  typedef ::inputfile_t inputfile_type;
  typedef ::xsd::cxx::tree::sequence< inputfile_type > inputfile_sequence;
  typedef inputfile_sequence::iterator inputfile_iterator;
  typedef inputfile_sequence::const_iterator inputfile_const_iterator;
  typedef ::xsd::cxx::tree::traits< inputfile_type, char > inputfile_traits;

  const inputfile_sequence&
  inputfile () const;

  inputfile_sequence&
  inputfile ();

  void
  inputfile (const inputfile_sequence& s);

  // outputfile
  // 
  typedef ::outputfile_t outputfile_type;
  typedef ::xsd::cxx::tree::traits< outputfile_type, char > outputfile_traits;

  const outputfile_type&
  outputfile () const;

  outputfile_type&
  outputfile ();

  void
  outputfile (const outputfile_type& x);

  void
  outputfile (::std::auto_ptr< outputfile_type > p);

  // Constructors.
  //
  pse_t (const start_time_type&,
         const t_end_type&,
         const delta_t_type&,
         const ljf_type&,
         const lc_type&,
         const outputfile_type&);

  pse_t (const start_time_type&,
         const t_end_type&,
         const delta_t_type&,
         ::std::auto_ptr< ljf_type >&,
         ::std::auto_ptr< lc_type >&,
         ::std::auto_ptr< outputfile_type >&);

  pse_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f = 0,
         ::xml_schema::container* c = 0);

  pse_t (const pse_t& x,
         ::xml_schema::flags f = 0,
         ::xml_schema::container* c = 0);

  virtual pse_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~pse_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< start_time_type > start_time_;
  ::xsd::cxx::tree::one< t_end_type > t_end_;
  ::xsd::cxx::tree::one< delta_t_type > delta_t_;
  ::xsd::cxx::tree::one< ljf_type > ljf_;
  ::xsd::cxx::tree::one< lc_type > lc_;
  inputfile_sequence inputfile_;
  ::xsd::cxx::tree::one< outputfile_type > outputfile_;
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

// Parse a URI or a local file.
//

::std::auto_ptr< ::pse_t >
pse (const ::std::string& uri,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (const ::std::string& uri,
     ::xml_schema::error_handler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (const ::std::string& uri,
     ::xercesc::DOMErrorHandler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse std::istream.
//

::std::auto_ptr< ::pse_t >
pse (::std::istream& is,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::std::istream& is,
     ::xml_schema::error_handler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::std::istream& is,
     ::xercesc::DOMErrorHandler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::std::istream& is,
     const ::std::string& id,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::std::istream& is,
     const ::std::string& id,
     ::xml_schema::error_handler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::std::istream& is,
     const ::std::string& id,
     ::xercesc::DOMErrorHandler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::InputSource.
//

::std::auto_ptr< ::pse_t >
pse (::xercesc::InputSource& is,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::xercesc::InputSource& is,
     ::xml_schema::error_handler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::xercesc::InputSource& is,
     ::xercesc::DOMErrorHandler& eh,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::DOMDocument.
//

::std::auto_ptr< ::pse_t >
pse (const ::xercesc::DOMDocument& d,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::pse_t >
pse (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
     ::xml_schema::flags f = 0,
     const ::xml_schema::properties& p = ::xml_schema::properties ());

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // INPUT_SETTING_HXX
