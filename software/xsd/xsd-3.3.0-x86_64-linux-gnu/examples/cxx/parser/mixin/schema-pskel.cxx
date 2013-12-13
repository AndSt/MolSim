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

#include "schema-pskel.hxx"

// base_pskel
//

void base_pskel::
a_parser (::xml_schema::boolean_pskel& p)
{
  this->a_parser_ = &p;
}

void base_pskel::
parsers (::xml_schema::boolean_pskel& a)
{
  this->a_parser_ = &a;
}

base_pskel::
base_pskel ()
: a_parser_ (0)
{
}

// derived_pskel
//

void derived_pskel::
b_parser (::xml_schema::int_pskel& p)
{
  this->b_parser_ = &p;
}

void derived_pskel::
parsers (::xml_schema::boolean_pskel& a,
         ::xml_schema::int_pskel& b)
{
  this->a_parser_ = &a;
  this->b_parser_ = &b;
}

derived_pskel::
derived_pskel ()
: b_parser_ (0)
{
}

// base_pskel
//

void base_pskel::
a (bool)
{
}

bool base_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "a" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->a_parser_;

    if (this->a_parser_)
      this->a_parser_->pre ();

    return true;
  }

  return false;
}

bool base_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::xml_schema::complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "a" && ns.empty ())
  {
    if (this->a_parser_)
      this->a (this->a_parser_->post_boolean ());

    return true;
  }

  return false;
}

// derived_pskel
//

void derived_pskel::
b (int)
{
}

bool derived_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::base_pskel::_start_element_impl (ns, n, t))
    return true;

  if (n == "b" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->b_parser_;

    if (this->b_parser_)
      this->b_parser_->pre ();

    return true;
  }

  return false;
}

bool derived_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::base_pskel::_end_element_impl (ns, n))
    return true;

  if (n == "b" && ns.empty ())
  {
    if (this->b_parser_)
      this->b (this->b_parser_->post_int ());

    return true;
  }

  return false;
}

// Begin epilogue.
//
//
// End epilogue.

