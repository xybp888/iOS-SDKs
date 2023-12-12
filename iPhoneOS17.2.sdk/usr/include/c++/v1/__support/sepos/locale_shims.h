// -*- C++ -*-
//===-----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SUPPORT_SEPOS_LOCALE_SHIMS_H
#define _LIBCPP___SUPPORT_SEPOS_LOCALE_SHIMS_H

#include <stddef.h> // Make sure to define NULL, which is technically required to be defined by <clocale>

// TODO: This is a hack to pretend that localization support is
//       present on SepOS. In reality, what we should do is teach
//       <iostream>, <regex> and others to work on top of a system
//       that truly does not support locales.
struct lconv {
    char*   decimal_point;
    char*   thousands_sep;
    char*   grouping;
    char*   int_curr_symbol;
    char*   currency_symbol;
    char*   mon_decimal_point;
    char*   mon_thousands_sep;
    char*   mon_grouping;
    char*   positive_sign;
    char*   negative_sign;
    char    int_frac_digits;
    char    frac_digits;
    char    p_cs_precedes;
    char    p_sep_by_space;
    char    n_cs_precedes;
    char    n_sep_by_space;
    char    p_sign_posn;
    char    n_sign_posn;
    char    int_p_cs_precedes;
    char    int_n_cs_precedes;
    char    int_p_sep_by_space;
    char    int_n_sep_by_space;
    char    int_p_sign_posn;
    char    int_n_sign_posn;
};

struct lconv* localeconv();

#define	LC_ALL		0
#define	LC_COLLATE	1
#define	LC_CTYPE	2
#define	LC_MONETARY	3
#define	LC_NUMERIC	4
#define	LC_TIME		5
#define	LC_MESSAGES	6

inline char* setlocale(int, const char *) {
    return "C";
}

#endif // _LIBCPP___SUPPORT_SEPOS_LOCALE_SHIMS_H
