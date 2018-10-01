/*
 * Copyright 2018 Yi-Soo An <yisooan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLS2_MACROS_H
#define GLS2_MACROS_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>

G_BEGIN_DECLS

#define LIBRARY_ID              "gls2"

#define PMLOG_CONTEXT_NAME      LIBRARY_ID
#define ERROR_MESSAGE_ID        LIBRARY_ID

#define NONE    (void)0

/* --- Useful macros --- */
#define     gls2_ret_false_if_fail(expr)      g_return_val_if_fail(expr, FALSE)
#define     gls2_ret_null_if_fail(expr)       g_return_val_if_fail(expr, NULL)

#define     gls2_ret_val_if_fail_autodef(_self, _privptr, _val) \
                do { \
                    g_return_val_if_fail (GLS2_IS_HANDLE (_self), _val); \
                    _privptr = (_self)->priv; \
                    g_return_val_if_fail ((_privptr)->handler != NULL, _val); \
                } while(FALSE)

#define     gls2_ret_false_if_fail_autodef(_self, _privptr) \
                gls2_ret_val_if_fail_autodef(_self, _privptr, FALSE)

#define     gls2_ret_null_if_fail_autodef(_self, _privptr) \
                gls2_ret_val_if_fail_autodef(_self, _privptr, NULL)

G_END_DECLS

#endif
