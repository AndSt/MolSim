// file      : examples/cxx/tree/hello/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain


#include <memory>   // std::auto_ptr

#include "InputSpheres.hxx"
#include <iostream>

using namespace std;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " Inputspheres.xml" << endl;
    return 1;
  }

  try
  {
	auto_ptr<spheres_t> h (spheres (argv[1], xml_schema::flags::dont_validate));
	cout << h->meshWidthS() << endl;
	spheres_t::sphere_const_iterator i (h->sphere().begin ());	
	cout << i->radiussph() << endl;
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    return 1;
  }
}



