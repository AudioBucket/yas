
// Copyright (c) 2010-2012 niXman (i dot nixman dog gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef _yas_test__version_hpp__included_
#define _yas_test__version_hpp__included_

template<typename archive_traits>
bool version_test(const char* archive_type) {
	typename archive_traits::oarchive_ptr oa = archive_traits::ocreate(archive_type);
	typename archive_traits::iarchive_ptr ia = archive_traits::icreate(archive_type, oa);

	if ( oa->archive_type() != ia->archive_type() ) {
		std::cout << "VERSION test failed! archive type is not equal! [1]" << std::endl;
		return false;
	}
	if ( oa->bits() != ia->bits() ) {
		std::cout << "VERSION test failed! archive bits is not equal! [2]" << std::endl;
		return false;
	}
	if ( oa->version() != ia->version() ) {
		std::cout << "VERSION test failed! archive versions is not equal! [3]" << std::endl;
		return false;
	}

	if ( yas::is_binary_archive<typename archive_traits::oarchive_type>::value ) {
		if ( oa->header_size() != archive_traits::oarchive_type::_header_size ||
			  archive_traits::oarchive_type::_header_size != sizeof(yas::uint32_t)
		) {
			std::cout << "VERSION test failed! bad archive header size! [4]" << std::endl;
			return false;
		}
	} else if ( yas::is_text_archive<typename archive_traits::oarchive_type>::value ) {
		if ( oa->header_size() != archive_traits::oarchive_type::_header_size ||
			  archive_traits::oarchive_type::_header_size != 5 /** see information.hpp */
		) {
			std::cout << "VERSION test failed! bad archive header size! [5]" << std::endl;
			return false;
		}
	} else if ( yas::is_json_archive<typename archive_traits::oarchive_type>::value ) {
	} else {
		std::cout << "VERSION test failed! bad archive type! [6]" << std::endl;
		return false;
	}
//   std::cout
//   << "binary_mem_oarchive: type = " << oa.archive_type() << std::endl
//   << "binary_mem_oarchive: bits = " << oa.bits() << std::endl
//   << "binary_mem_oarchive: vers = " << oa.version() << std::endl << std::endl;
//   std::cout
//   << "binary_mem_iarchive: type = " << ia.archive_type() << std::endl
//   << "binary_mem_iarchive: bits = " << ia.bits() << std::endl
//   << "binary_mem_iarchive: vers = " << ia.version() << std::endl << std::endl;

	return true;
}

#endif // _yas_test__version_hpp__included_
