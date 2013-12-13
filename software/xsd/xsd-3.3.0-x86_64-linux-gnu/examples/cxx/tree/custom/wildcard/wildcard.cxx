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

#include <xsd/cxx/pre.hxx>

#include "wildcard.hxx"

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace wildcard
{
  // data_base
  //

  data_base::
  data_base ()
  : ::xml_schema::string (),
    id_ (::xml_schema::flags (), this)
  {
  }

  data_base::
  data_base (const char* _xsd_string_base)
  : ::xml_schema::string (_xsd_string_base),
    id_ (::xml_schema::flags (), this)
  {
  }

  data_base::
  data_base (const ::std::string& _xsd_string_base)
  : ::xml_schema::string (_xsd_string_base),
    id_ (::xml_schema::flags (), this)
  {
  }

  data_base::
  data_base (const ::xml_schema::string& _xsd_string_base)
  : ::xml_schema::string (_xsd_string_base),
    id_ (::xml_schema::flags (), this)
  {
  }

  data_base::
  data_base (const data_base& x,
             ::xml_schema::flags f,
             ::xml_schema::container* c)
  : ::xml_schema::string (x, f, c),
    id_ (x.id_, f, this)
  {
  }

  data_base::
  data_base (const ::xercesc::DOMElement& e,
             ::xml_schema::flags f,
             ::xml_schema::container* c)
  : ::xml_schema::string (e, f | ::xml_schema::flags::base, c),
    id_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
      this->parse (p, f);
    }
  }

  void data_base::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "id" && n.namespace_ ().empty ())
      {
        this->id_.set (id_traits::create (i, f, this));
        continue;
      }
    }
  }

  data_base* data_base::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class data_base (*this, f, c);
  }

  data_base::
  ~data_base ()
  {
  }
}

#include <ostream>

namespace wildcard
{
  ::std::ostream&
  operator<< (::std::ostream& o, const data_base& i)
  {
    o << static_cast< const ::xml_schema::string& > (i);

    if (i.id ())
    {
      o << ::std::endl << "id: " << *i.id ();
    }

    return o;
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace wildcard
{
  ::std::auto_ptr< ::wildcard::data >
  data_ (const ::std::string& u,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::wildcard::data > r (
      ::wildcard::data_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (const ::std::string& u,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::wildcard::data > r (
      ::wildcard::data_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (const ::std::string& u,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::wildcard::data > r (
      ::wildcard::data_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::std::istream& is,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::wildcard::data_ (isrc, f, p);
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::std::istream& is,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::wildcard::data_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::std::istream& is,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::wildcard::data_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::wildcard::data_ (isrc, f, p);
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::wildcard::data_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::std::istream& is,
         const ::std::string& sid,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::wildcard::data_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::xercesc::InputSource& i,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::wildcard::data > r (
      ::wildcard::data_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::xercesc::InputSource& i,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::wildcard::data > r (
      ::wildcard::data_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::xercesc::InputSource& i,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::wildcard::data > r (
      ::wildcard::data_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (const ::xercesc::DOMDocument& d,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
  {
    if (f & ::xml_schema::flags::keep_dom)
    {
      ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
        static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

      ::std::auto_ptr< ::wildcard::data > r (
        ::wildcard::data_ (
          c, f | ::xml_schema::flags::own_dom, p));

      return r;
    }

    const ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "data" &&
        n.namespace_ () == "http://www.codesynthesis.com/wildcard")
    {
      ::std::auto_ptr< ::wildcard::data > r (
        ::xsd::cxx::tree::traits< ::wildcard::data, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "data",
      "http://www.codesynthesis.com/wildcard");
  }

  ::std::auto_ptr< ::wildcard::data >
  data_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
         ::xml_schema::flags f,
         const ::xml_schema::properties&)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      ((f & ::xml_schema::flags::keep_dom) &&
       !(f & ::xml_schema::flags::own_dom))
      ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
      : 0);

    ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (f & ::xml_schema::flags::keep_dom)
      doc.setUserData (::xml_schema::dom::tree_node_key,
                       (c.get () ? &c : &d),
                       0);

    if (n.name () == "data" &&
        n.namespace_ () == "http://www.codesynthesis.com/wildcard")
    {
      ::std::auto_ptr< ::wildcard::data > r (
        ::xsd::cxx::tree::traits< ::wildcard::data, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "data",
      "http://www.codesynthesis.com/wildcard");
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace wildcard
{
  void
  operator<< (::xercesc::DOMElement& e, const data_base& i)
  {
    e << static_cast< const ::xml_schema::string& > (i);

    // id
    //
    if (i.id ())
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "id",
          e));

      a << *i.id ();
    }
  }

  void
  data_ (::std::ostream& o,
         const ::wildcard::data& s,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::wildcard::data_ (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  data_ (::std::ostream& o,
         const ::wildcard::data& s,
         ::xml_schema::error_handler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::wildcard::data_ (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  data_ (::std::ostream& o,
         const ::wildcard::data& s,
         ::xercesc::DOMErrorHandler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::wildcard::data_ (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  data_ (::xercesc::XMLFormatTarget& t,
         const ::wildcard::data& s,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::wildcard::data_ (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  data_ (::xercesc::XMLFormatTarget& t,
         const ::wildcard::data& s,
         ::xml_schema::error_handler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::wildcard::data_ (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  data_ (::xercesc::XMLFormatTarget& t,
         const ::wildcard::data& s,
         ::xercesc::DOMErrorHandler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::wildcard::data_ (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  data_ (::xercesc::DOMDocument& d,
         const ::wildcard::data& s,
         ::xml_schema::flags)
  {
    ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "data" &&
        n.namespace_ () == "http://www.codesynthesis.com/wildcard")
    {
      e << s;
    }
    else
    {
      throw ::xsd::cxx::tree::unexpected_element < char > (
        n.name (),
        n.namespace_ (),
        "data",
        "http://www.codesynthesis.com/wildcard");
    }
  }

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
  data_ (const ::wildcard::data& s,
         const ::xml_schema::namespace_infomap& m,
         ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::serialize< char > (
        "data",
        "http://www.codesynthesis.com/wildcard",
        m, f));

    ::wildcard::data_ (*d, s, f);
    return d;
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

