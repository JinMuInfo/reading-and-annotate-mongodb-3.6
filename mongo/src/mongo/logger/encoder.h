/*    Copyright 2013 10gen Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects
 *    for all of the code used other than as permitted herein. If you modify
 *    file(s) with this exception, you may extend this exception to your
 *    version of the file(s), but you are not obligated to do so. If you do not
 *    wish to do so, delete this exception statement from your version. If you
 *    delete this exception statement from all source files in the program,
 *    then also delete it in the license file.
 */

#pragma once

#include <iosfwd>

namespace mongo {
namespace logger {

/**
 * Interface for objects that encode Events to std::ostreams.
 *
 * Most appender implementations write to streams, and Encoders represent the process of
 * encoding events into streams.
 */
 /*
Encoder
Encoder类负责对日志格式化，在不同的场景可能需要不同格式的日志，比如输出到console和文件可以使用一种格式，输出到syslog用另一种格式，还有些时候是不需要特定格式，直接输出raw信息即可。那么只要定义一个特定格式的派生类，实现对应的encode()接口即可。MongoDB目前定义了以下3种Encoder分别用于console/文件、syslog和raw：

MessageEventDetailsEncoder
MessageEventWithContextEncoder
MessageEventUnadornedEncoder
*/
template <typename Event>
class Encoder {
public:
    virtual ~Encoder() {}
    virtual std::ostream& encode(const Event& event, std::ostream& os) = 0;
};

}  // namespace logger
}  // nnamspace mongo
