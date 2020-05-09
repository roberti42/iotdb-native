/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef IOTDB_NATIVE_RWIO_H
#define IOTDB_NATIVE_RWIO_H

#include <optional>
#include <string>

#include "tsfile/file/metadata/metadata.h"
#include "util/bytebuffer.h"
#include "util/bconv.h"

#include <iostream>

using namespace iotdb::tsfile::file::metadata;

namespace iotdb {
    namespace rwio {
        constexpr std::size_t BOOL_LEN = 1;
        constexpr std::size_t SHORT_LEN = 2;
        constexpr std::size_t INT_LEN = 4;
        constexpr std::size_t LONG_LEN = 8;
        constexpr std::size_t DOUBLE_LEN = 8;
        constexpr std::size_t FLOAT_LEN = 4;

        /**( READ BASE TYPES )**/

        template<typename Tp = bool, typename InputStream>
        std::optional <Tp>
        read(InputStream& bstream) {
            int32_t len;
            if (std::is_same_v < Tp, std::string >) {
                len = read<int32_t>(bstream).value_or(-1);
            } else {
                len = sizeof(Tp);
            }
            std::optional <iotdb::vbytes> res = bstream.read_n(len);
            if (!res) {
                return {};
            }
            return bconv::to<Tp>(res.value());
        }

        /**( READ ENUMS )**/

        template<typename Tp, typename InputStream>
        std::optional <Tp>
        read_enum(InputStream& bstream) {
            std::optional <int16_t> res = read<int16_t>(bstream);
            if (!res) {
                return {};
            }
            return static_cast<Tp>(res.value());
        }

        /**( READ CONTAINERS )**/

        template<typename Tp, typename InputStream>
        std::vector <Tp>
        read_list(InputStream &bstream) {
            int32_t len = read<int32_t>(bstream).value_or(0);
            if (len <= 0) {
                return {};
            }
            std::vector <Tp> res;
            res.reserve(len);
            for (int i = 0; i < len; ++i) {
                res.push_back(read<Tp>(bstream).value());
            }
            return res;
        }

        template<typename InputStream> std::string read_string(InputStream& bstream) {
            int32_t len = read<int32_t>(bstream).value_or(0);
            if (len <= 0) {
                return {};
            }
            std::string res;
            res.reserve(len);
            for (int i = 0; i < len; ++i) {
                res.push_back(read<char>(bstream).value());
            }
            return res;
        }
    }
}

#endif // IOTDB_NATIVE_RWIO_H
