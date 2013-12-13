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

#ifndef ORDER_IXX
#define ORDER_IXX

// Begin prologue.
//
//
// End prologue.

// item
// 

inline
const item::name_type& item::
name () const
{
  return this->name_.get ();
}

inline
item::name_type& item::
name ()
{
  return this->name_.get ();
}

inline
void item::
name (const name_type& x)
{
  this->name_.set (x);
}

inline
void item::
name (::std::auto_ptr< name_type > x)
{
  this->name_.set (x);
}

inline
const item::price_type& item::
price () const
{
  return this->price_.get ();
}

inline
item::price_type& item::
price ()
{
  return this->price_.get ();
}

inline
void item::
price (const price_type& x)
{
  this->price_.set (x);
}


// order
// 

inline
const order::item_sequence& order::
item () const
{
  return this->item_;
}

inline
order::item_sequence& order::
item ()
{
  return this->item_;
}

inline
void order::
item (const item_sequence& s)
{
  this->item_ = s;
}


// Begin epilogue.
//
//
// End epilogue.

#endif // ORDER_IXX
