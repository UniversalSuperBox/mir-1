/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#include "native_buffer.h"
#include "ipc_operations.h"
#include "mir/graphics/platform_operation_message.h"
#include "mir/graphics/buffer.h"
#include "mir/graphics/buffer_ipc_message.h"

namespace mg = mir::graphics;
namespace mgn = mir::graphics::nested;
namespace geom = mir::geometry;

mgn::IpcOperations::IpcOperations(
    std::shared_ptr<mg::PlatformIpcOperations> const& host_operations) :
    ipc_operations(host_operations)
{
}

void mgn::IpcOperations::pack_buffer(
    mg::BufferIpcMessage& message, mg::Buffer const& buffer, mg::BufferIpcMsgType msg_type) const
{
    auto native = std::dynamic_pointer_cast<mgn::NativeBuffer>(buffer.native_buffer_handle());
    if (!native)
    {
        ipc_operations->pack_buffer(message, buffer, msg_type);
    }
    else
    {
        if (msg_type == mg::BufferIpcMsgType::full_msg)
        {
            auto package = native->package();
            for (auto i = 0; i < package->data_items; i++)
                message.pack_data(package->data[i]);
            for (auto i = 0; i < package->fd_items; i++)
                message.pack_data(mir::Fd(IntOwnedFd{package->fd[i]}));
            message.pack_stride(geom::Stride{package->stride});
            message.pack_flags(package->flags);
            message.pack_size(geom::Size{package->width, package->height});
        }
        else
        {
        }
    }
}

void mgn::IpcOperations::unpack_buffer(mg::BufferIpcMessage& message, mg::Buffer const& buffer) const
{
    (void)message; (void)buffer;
}

std::shared_ptr<mg::PlatformIPCPackage> mgn::IpcOperations::connection_ipc_package()
{
    return ipc_operations->connection_ipc_package();
}

mg::PlatformOperationMessage mgn::IpcOperations::platform_operation(
    unsigned int const opcode, mg::PlatformOperationMessage const& message)
{
    return ipc_operations->platform_operation(opcode, message);
}
