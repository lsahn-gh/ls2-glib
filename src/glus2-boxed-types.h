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

#ifndef GLUS2_BOXED_TYPES_H
#define GLUS2_BOXED_TYPES_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>

G_BEGIN_DECLS

/* 
 * DO NOT use boxed-LSHandle unless you know how it works exactly.
 * There could be memory leak issues.
 */
#define     GLUS2_TYPE_LSHANDLE          (glus2_lshandle_get_type ())
GType       glus2_lshandle_get_type      (void);

#define     GLUS2_TYPE_LSMETHOD          (glus2_lsmethod_get_type ())
GType       glus2_lsmethod_get_type      (void);

#define     GLUS2_TYPE_LSSIGNAL          (glus2_lssignal_get_type ())
GType       glus2_lssignal_get_type      (void);

#define     GLUS2_TYPE_LSPROPERTY        (glus2_lsproperty_get_type ())
GType       glus2_lsproperty_get_type    (void);

G_END_DECLS

#endif
