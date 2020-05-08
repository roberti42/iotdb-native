/* Licensed to the Apache Software Foundation (ASF) under one
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

#include <chunk_header.h>
#include <iostream>
#include <metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace header {

                using namespace iotdb::tsfile::file::metadata;

                /**
                         * Class that holds the responsibility to model a chunk header
                         */

                /**
                         * Construct a chunk header
                         * @param measurementID     id of measurement
                         * @param dataSize          size of the data
                         * @param headerSize        size of the header
                         * @param dataType          type of the data
                         * @param compressionType   type of compression
                         * @param encoding          type of encoding
                         * @param numOfPages        numeber of pages
                         */
                chunk_header::chunk_header(std::string measurementID,
                                           int dataSize,
                                           int headerSize,
                                           ts_datatype dataType,
                                           compression_type compressionType,
                                           ts_encoding encoding,
                                           int numOfPages) : _measurement_id(measurementID),
                                                            _data_size(dataSize),
                                                            _datatype(dataType),
                                                            _compression_type(compressionType),
                                                            _encoding_type(encoding),
                                                            _num_of_pages(numOfPages){
                }

                size_t chunk_header::to_buffer(bytebuffer &buffer) {

                }

                std::string chunk_header::get_measurement_id() const {
                    return _measurement_id;
                }

                void chunk_header::set_measurement_id(const std::string &id) const {
                    _measurement_id = id;
                }

                compression_type chunk_header::get_compression_type() const {
                    return _compression_type;
                }

                void chunk_header::
                set_compression_type(const compression_type &type) const {
                    _compression_type = type;
                }

                ts_datatype chunk_header::get_ts_datatype() const {

                }

                void chunk_header::set_ts_datatype(const ts_datatype &type) const;

                ts_encoding chunk_header::get_ts_encoding() const;

                void chunk_header::set_ts_encoding(const ts_encoding &type) const;

                int chunk_header::get_num_of_pages() const;

                void chunk_header::set_num_of_pages(const int &num_of_pages);

                std::string chunk_header::str() const;
            }
        }
    }
}
