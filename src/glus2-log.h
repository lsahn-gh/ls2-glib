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

#ifndef GLUS2_LOG_H
#define GLUS2_LOG_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>
#include <PmLogLib.h>

G_BEGIN_DECLS

PmLogContext    glus2_pmlog_get_context (void);

#define glus2_log_err(...)       PmLogPrintError(glus2_pmlog_get_context(), __VA_ARGS__)
#define glus2_log_warn(...)      PmLogPrintWarning(glus2_pmlog_get_context(), __VA_ARGS__)
#define glus2_log_info(...)      PmLogPrintInfo(glus2_pmlog_get_context(), __VA_ARGS__)
#define glus2_log_debug(...)     PmLogPrintDebug(glus2_pmlog_get_context(), __VA_ARGS__)

/*
 * - lserror_print_if_set
 * - lserror_log_if_set
 * 
 * NONE is used to prevent that both are assigned to variables accidentally.
 * 
 * @return None
 */
#define glus2_err_print_if_set(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorPrint (lserrptr, stderr); \
        LSErrorFree (lserrptr); \
    }

#define glus2_err_print_if_set_without_free(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorPrint (lserrptr, stderr); \
    }

#define glus2_err_log_if_set(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorLog (glus2_pmlog_get_context (), ERROR_MESSAGE_ID, lserrptr); \
        LSErrorFree (lserrptr); \
    }

#define glus2_err_log_if_set_without_free(lserrptr) \
    if (LSErrorIsSet (lserrptr)) { \
        LSErrorLog (glus2_pmlog_get_context (), ERROR_MESSAGE_ID, lserrptr); \
    }

G_END_DECLS

#endif