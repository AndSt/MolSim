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

#include "InputSpheres.h"

// centerPos_t
// 

const centerPos_t::x_type& centerPos_t::
x () const
{
  return this->x_.get ();
}

centerPos_t::x_type& centerPos_t::
x ()
{
  return this->x_.get ();
}

void centerPos_t::
x (const x_type& x)
{
  this->x_.set (x);
}

const centerPos_t::y_type& centerPos_t::
y () const
{
  return this->y_.get ();
}

centerPos_t::y_type& centerPos_t::
y ()
{
  return this->y_.get ();
}

void centerPos_t::
y (const y_type& x)
{
  this->y_.set (x);
}

const centerPos_t::z_type& centerPos_t::
z () const
{
  return this->z_.get ();
}

centerPos_t::z_type& centerPos_t::
z ()
{
  return this->z_.get ();
}

void centerPos_t::
z (const z_type& x)
{
  this->z_.set (x);
}


// startVel_t
// 

const startVel_t::vX_type& startVel_t::
vX () const
{
  return this->vX_.get ();
}

startVel_t::vX_type& startVel_t::
vX ()
{
  return this->vX_.get ();
}

void startVel_t::
vX (const vX_type& x)
{
  this->vX_.set (x);
}

const startVel_t::vY_type& startVel_t::
vY () const
{
  return this->vY_.get ();
}

startVel_t::vY_type& startVel_t::
vY ()
{
  return this->vY_.get ();
}

void startVel_t::
vY (const vY_type& x)
{
  this->vY_.set (x);
}

const startVel_t::vZ_type& startVel_t::
vZ () const
{
  return this->vZ_.get ();
}

startVel_t::vZ_type& startVel_t::
vZ ()
{
  return this->vZ_.get ();
}

void startVel_t::
vZ (const vZ_type& x)
{
  this->vZ_.set (x);
}


// sphere_t
// 

const sphere_t::centerPos_type& sphere_t::
centerPos () const
{
  return this->centerPos_.get ();
}

sphere_t::centerPos_type& sphere_t::
centerPos ()
{
  return this->centerPos_.get ();
}

void sphere_t::
centerPos (const centerPos_type& x)
{
  this->centerPos_.set (x);
}

void sphere_t::
centerPos (::std::auto_ptr< centerPos_type > x)
{
  this->centerPos_.set (x);
}

const sphere_t::startVel_type& sphere_t::
startVel () const
{
  return this->startVel_.get ();
}

sphere_t::startVel_type& sphere_t::
startVel ()
{
  return this->startVel_.get ();
}

void sphere_t::
startVel (const startVel_type& x)
{
  this->startVel_.set (x);
}

void sphere_t::
startVel (::std::auto_ptr< startVel_type > x)
{
  this->startVel_.set (x);
}

const sphere_t::radiusS_type& sphere_t::
radiusS () const
{
  return this->radiusS_.get ();
}

sphere_t::radiusS_type& sphere_t::
radiusS ()
{
  return this->radiusS_.get ();
}

void sphere_t::
radiusS (const radiusS_type& x)
{
  this->radiusS_.set (x);
}


// spheres_t
// 

const spheres_t::meshWidthS_type& spheres_t::
meshWidthS () const
{
  return this->meshWidthS_.get ();
}

spheres_t::meshWidthS_type& spheres_t::
meshWidthS ()
{
  return this->meshWidthS_.get ();
}

void spheres_t::
meshWidthS (const meshWidthS_type& x)
{
  this->meshWidthS_.set (x);
}

const spheres_t::massS_type& spheres_t::
massS () const
{
  return this->massS_.get ();
}

spheres_t::massS_type& spheres_t::
massS ()
{
  return this->massS_.get ();
}

void spheres_t::
massS (const massS_type& x)
{
  this->massS_.set (x);
}

const spheres_t::meanVS_type& spheres_t::
meanVS () const
{
  return this->meanVS_.get ();
}

spheres_t::meanVS_type& spheres_t::
meanVS ()
{
  return this->meanVS_.get ();
}

void spheres_t::
meanVS (const meanVS_type& x)
{
  this->meanVS_.set (x);
}

const spheres_t::sphere_sequence& spheres_t::
sphere () const
{
  return this->sphere_;
}

spheres_t::sphere_sequence& spheres_t::
sphere ()
{
  return this->sphere_;
}

void spheres_t::
sphere (const sphere_sequence& s)
{
  this->sphere_ = s;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// centerPos_t
//

centerPos_t::
centerPos_t (const x_type& x,
             const y_type& y,
             const z_type& z)
: ::xml_schema::type (),
  x_ (x, ::xml_schema::flags (), this),
  y_ (y, ::xml_schema::flags (), this),
  z_ (z, ::xml_schema::flags (), this)
{
}

centerPos_t::
centerPos_t (const centerPos_t& x,
             ::xml_schema::flags f,
             ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  x_ (x.x_, f, this),
  y_ (x.y_, f, this),
  z_ (x.z_, f, this)
{
}

centerPos_t::
centerPos_t (const ::xercesc::DOMElement& e,
             ::xml_schema::flags f,
             ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  x_ (f, this),
  y_ (f, this),
  z_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void centerPos_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // x
    //
    if (n.name () == "x" && n.namespace_ ().empty ())
    {
      if (!x_.present ())
      {
        this->x_.set (x_traits::create (i, f, this));
        continue;
      }
    }

    // y
    //
    if (n.name () == "y" && n.namespace_ ().empty ())
    {
      if (!y_.present ())
      {
        this->y_.set (y_traits::create (i, f, this));
        continue;
      }
    }

    // z
    //
    if (n.name () == "z" && n.namespace_ ().empty ())
    {
      if (!z_.present ())
      {
        this->z_.set (z_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!x_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "x",
      "");
  }

  if (!y_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "y",
      "");
  }

  if (!z_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "z",
      "");
  }
}

centerPos_t* centerPos_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class centerPos_t (*this, f, c);
}

centerPos_t::
~centerPos_t ()
{
}

// startVel_t
//

startVel_t::
startVel_t (const vX_type& vX,
            const vY_type& vY,
            const vZ_type& vZ)
: ::xml_schema::type (),
  vX_ (vX, ::xml_schema::flags (), this),
  vY_ (vY, ::xml_schema::flags (), this),
  vZ_ (vZ, ::xml_schema::flags (), this)
{
}

startVel_t::
startVel_t (const startVel_t& x,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  vX_ (x.vX_, f, this),
  vY_ (x.vY_, f, this),
  vZ_ (x.vZ_, f, this)
{
}

startVel_t::
startVel_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  vX_ (f, this),
  vY_ (f, this),
  vZ_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void startVel_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // vX
    //
    if (n.name () == "vX" && n.namespace_ ().empty ())
    {
      if (!vX_.present ())
      {
        this->vX_.set (vX_traits::create (i, f, this));
        continue;
      }
    }

    // vY
    //
    if (n.name () == "vY" && n.namespace_ ().empty ())
    {
      if (!vY_.present ())
      {
        this->vY_.set (vY_traits::create (i, f, this));
        continue;
      }
    }

    // vZ
    //
    if (n.name () == "vZ" && n.namespace_ ().empty ())
    {
      if (!vZ_.present ())
      {
        this->vZ_.set (vZ_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!vX_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "vX",
      "");
  }

  if (!vY_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "vY",
      "");
  }

  if (!vZ_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "vZ",
      "");
  }
}

startVel_t* startVel_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class startVel_t (*this, f, c);
}

startVel_t::
~startVel_t ()
{
}

// sphere_t
//

sphere_t::
sphere_t (const centerPos_type& centerPos,
          const startVel_type& startVel,
          const radiusS_type& radiusS)
: ::xml_schema::type (),
  centerPos_ (centerPos, ::xml_schema::flags (), this),
  startVel_ (startVel, ::xml_schema::flags (), this),
  radiusS_ (radiusS, ::xml_schema::flags (), this)
{
}

sphere_t::
sphere_t (::std::auto_ptr< centerPos_type >& centerPos,
          ::std::auto_ptr< startVel_type >& startVel,
          const radiusS_type& radiusS)
: ::xml_schema::type (),
  centerPos_ (centerPos, ::xml_schema::flags (), this),
  startVel_ (startVel, ::xml_schema::flags (), this),
  radiusS_ (radiusS, ::xml_schema::flags (), this)
{
}

sphere_t::
sphere_t (const sphere_t& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  centerPos_ (x.centerPos_, f, this),
  startVel_ (x.startVel_, f, this),
  radiusS_ (x.radiusS_, f, this)
{
}

sphere_t::
sphere_t (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  centerPos_ (f, this),
  startVel_ (f, this),
  radiusS_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void sphere_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // centerPos
    //
    if (n.name () == "centerPos" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< centerPos_type > r (
        centerPos_traits::create (i, f, this));

      if (!centerPos_.present ())
      {
        this->centerPos_.set (r);
        continue;
      }
    }

    // startVel
    //
    if (n.name () == "startVel" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< startVel_type > r (
        startVel_traits::create (i, f, this));

      if (!startVel_.present ())
      {
        this->startVel_.set (r);
        continue;
      }
    }

    // radiusS
    //
    if (n.name () == "radiusS" && n.namespace_ ().empty ())
    {
      if (!radiusS_.present ())
      {
        this->radiusS_.set (radiusS_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!centerPos_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "centerPos",
      "");
  }

  if (!startVel_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "startVel",
      "");
  }

  if (!radiusS_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "radiusS",
      "");
  }
}

sphere_t* sphere_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class sphere_t (*this, f, c);
}

sphere_t::
~sphere_t ()
{
}

// spheres_t
//

spheres_t::
spheres_t (const meshWidthS_type& meshWidthS,
           const massS_type& massS,
           const meanVS_type& meanVS)
: ::xml_schema::type (),
  meshWidthS_ (meshWidthS, ::xml_schema::flags (), this),
  massS_ (massS, ::xml_schema::flags (), this),
  meanVS_ (meanVS, ::xml_schema::flags (), this),
  sphere_ (::xml_schema::flags (), this)
{
}

spheres_t::
spheres_t (const spheres_t& x,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  meshWidthS_ (x.meshWidthS_, f, this),
  massS_ (x.massS_, f, this),
  meanVS_ (x.meanVS_, f, this),
  sphere_ (x.sphere_, f, this)
{
}

spheres_t::
spheres_t (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  meshWidthS_ (f, this),
  massS_ (f, this),
  meanVS_ (f, this),
  sphere_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void spheres_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // meshWidthS
    //
    if (n.name () == "meshWidthS" && n.namespace_ ().empty ())
    {
      if (!meshWidthS_.present ())
      {
        this->meshWidthS_.set (meshWidthS_traits::create (i, f, this));
        continue;
      }
    }

    // massS
    //
    if (n.name () == "massS" && n.namespace_ ().empty ())
    {
      if (!massS_.present ())
      {
        this->massS_.set (massS_traits::create (i, f, this));
        continue;
      }
    }

    // meanVS
    //
    if (n.name () == "meanVS" && n.namespace_ ().empty ())
    {
      if (!meanVS_.present ())
      {
        this->meanVS_.set (meanVS_traits::create (i, f, this));
        continue;
      }
    }

    // sphere
    //
    if (n.name () == "sphere" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< sphere_type > r (
        sphere_traits::create (i, f, this));

      this->sphere_.push_back (r);
      continue;
    }

    break;
  }

  if (!meshWidthS_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "meshWidthS",
      "");
  }

  if (!massS_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "massS",
      "");
  }

  if (!meanVS_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "meanVS",
      "");
  }
}

spheres_t* spheres_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class spheres_t (*this, f, c);
}

spheres_t::
~spheres_t ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::spheres_t >
spheres (const ::std::string& u,
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

  ::std::auto_ptr< ::spheres_t > r (
    ::spheres (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::spheres_t >
spheres (const ::std::string& u,
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

  ::std::auto_ptr< ::spheres_t > r (
    ::spheres (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::spheres_t >
spheres (const ::std::string& u,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::spheres_t > r (
    ::spheres (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::spheres_t >
spheres (::std::istream& is,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::spheres (isrc, f, p);
}

::std::auto_ptr< ::spheres_t >
spheres (::std::istream& is,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::spheres (isrc, h, f, p);
}

::std::auto_ptr< ::spheres_t >
spheres (::std::istream& is,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::spheres (isrc, h, f, p);
}

::std::auto_ptr< ::spheres_t >
spheres (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::spheres (isrc, f, p);
}

::std::auto_ptr< ::spheres_t >
spheres (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::spheres (isrc, h, f, p);
}

::std::auto_ptr< ::spheres_t >
spheres (::std::istream& is,
         const ::std::string& sid,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::spheres (isrc, h, f, p);
}

::std::auto_ptr< ::spheres_t >
spheres (::xercesc::InputSource& i,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::spheres_t > r (
    ::spheres (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::spheres_t >
spheres (::xercesc::InputSource& i,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::spheres_t > r (
    ::spheres (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::spheres_t >
spheres (::xercesc::InputSource& i,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::spheres_t > r (
    ::spheres (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::spheres_t >
spheres (const ::xercesc::DOMDocument& d,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

    ::std::auto_ptr< ::spheres_t > r (
      ::spheres (
        c, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  const ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "spheres" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::spheres_t > r (
      ::xsd::cxx::tree::traits< ::spheres_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "spheres",
    "");
}

::std::auto_ptr< ::spheres_t >
spheres (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
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

  if (n.name () == "spheres" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::spheres_t > r (
      ::xsd::cxx::tree::traits< ::spheres_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "spheres",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

