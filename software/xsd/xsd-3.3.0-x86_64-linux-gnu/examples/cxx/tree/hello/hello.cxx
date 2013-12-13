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

#include "hello.hxx"

// hello_t
// 

const hello_t::greeting_type& hello_t::
greeting () const
{
  return this->greeting_.get ();
}

hello_t::greeting_type& hello_t::
greeting ()
{
  return this->greeting_.get ();
}

void hello_t::
greeting (const greeting_type& x)
{
  this->greeting_.set (x);
}

void hello_t::
greeting (::std::auto_ptr< greeting_type > x)
{
  this->greeting_.set (x);
}

const hello_t::name_sequence& hello_t::
name () const
{
  return this->name_;
}

hello_t::name_sequence& hello_t::
name ()
{
  return this->name_;
}

void hello_t::
name (const name_sequence& s)
{
  this->name_ = s;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// hello_t
//

hello_t::
hello_t (const greeting_type& greeting)
: ::xml_schema::type (),
  greeting_ (greeting, ::xml_schema::flags (), this),
  name_ (::xml_schema::flags (), this)
{
}

hello_t::
hello_t (const hello_t& x,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  greeting_ (x.greeting_, f, this),
  name_ (x.name_, f, this)
{
}

hello_t::
hello_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  greeting_ (f, this),
  name_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void hello_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // greeting
    //
    if (n.name () == "greeting" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< greeting_type > r (
        greeting_traits::create (i, f, this));

      if (!greeting_.present ())
      {
        this->greeting_.set (r);
        continue;
      }
    }

    // name
    //
    if (n.name () == "name" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< name_type > r (
        name_traits::create (i, f, this));

      this->name_.push_back (r);
      continue;
    }

    break;
  }

  if (!greeting_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "greeting",
      "");
  }
}

hello_t* hello_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class hello_t (*this, f, c);
}

hello_t::
~hello_t ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::hello_t >
hello (const ::std::string& u,
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

  ::std::auto_ptr< ::hello_t > r (
    ::hello (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::hello_t >
hello (const ::std::string& u,
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

  ::std::auto_ptr< ::hello_t > r (
    ::hello (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::hello_t >
hello (const ::std::string& u,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::hello_t > r (
    ::hello (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::hello_t >
hello (::std::istream& is,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::hello (isrc, f, p);
}

::std::auto_ptr< ::hello_t >
hello (::std::istream& is,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::hello (isrc, h, f, p);
}

::std::auto_ptr< ::hello_t >
hello (::std::istream& is,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::hello (isrc, h, f, p);
}

::std::auto_ptr< ::hello_t >
hello (::std::istream& is,
       const ::std::string& sid,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::hello (isrc, f, p);
}

::std::auto_ptr< ::hello_t >
hello (::std::istream& is,
       const ::std::string& sid,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::hello (isrc, h, f, p);
}

::std::auto_ptr< ::hello_t >
hello (::std::istream& is,
       const ::std::string& sid,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::hello (isrc, h, f, p);
}

::std::auto_ptr< ::hello_t >
hello (::xercesc::InputSource& i,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::hello_t > r (
    ::hello (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::hello_t >
hello (::xercesc::InputSource& i,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::hello_t > r (
    ::hello (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::hello_t >
hello (::xercesc::InputSource& i,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::hello_t > r (
    ::hello (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::hello_t >
hello (const ::xercesc::DOMDocument& d,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

    ::std::auto_ptr< ::hello_t > r (
      ::hello (
        c, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  const ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "hello" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::hello_t > r (
      ::xsd::cxx::tree::traits< ::hello_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "hello",
    "");
}

::std::auto_ptr< ::hello_t >
hello (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
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

  if (n.name () == "hello" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::hello_t > r (
      ::xsd::cxx::tree::traits< ::hello_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "hello",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

