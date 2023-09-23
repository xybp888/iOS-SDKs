// -*- C++ -*-
//===-----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This adds support for the extended locale functions that are currently
// missing from the SepOS C library.
//
// This only works when the specified locale is "C" or "POSIX", but that's
// about as good as we can do without implementing full xlocale support
// in SepOS.
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SUPPORT_SEPOS_XLOCALE_H
#define _LIBCPP___SUPPORT_SEPOS_XLOCALE_H

#include <__support/xlocale/__nop_locale_mgmt.h>
#include <__support/xlocale/__posix_l_fallback.h>
#include <__support/xlocale/__strtonum_fallback.h>

#endif // _LIBCPP___SUPPORT_SEPOS_XLOCALE_H
