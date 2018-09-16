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

#ifndef GLS2_LOG_H
#define GLS2_LOG_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>
#include <PmLogLib.h>

G_BEGIN_DECLS

PmLogContext    gls2_pmlog_get_context (void);

#define gls2_log_err(...)       PmLogPrintError(gls2_pmlog_get_context(), __VA_ARGS__)
#define gls2_log_warn(...)      PmLogPrintWarning(gls2_pmlog_get_context(), __VA_ARGS__)
#define gls2_log_info(...)      PmLogPrintInfo(gls2_pmlog_get_context(), __VA_ARGS__)
#define gls2_log_debug(...)     PmLogPrintDebug(gls2_pmlog_get_context(), __VA_ARGS__)

#define gls2_err_print_if_set(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorPrint (lserrptr, stderr); \
        LSErrorFree (lserrptr); \
    }

#define gls2_err_print_if_set_without_free(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorPrint (lserrptr, stderr); \
    }

#define gls2_err_log_if_set(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorLog (gls2_pmlog_get_context (), ERROR_MESSAGE_ID, lserrptr); \
        LSErrorFree (lserrptr); \
    }

#define gls2_err_log_if_set_without_free(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorLog (gls2_pmlog_get_context (), ERROR_MESSAGE_ID, lserrptr); \
    }

G_END_DECLS

#endif
