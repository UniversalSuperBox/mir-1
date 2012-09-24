/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by:
 *  Alan Griffiths <alan@octopull.co.uk>
 *  Thomas Voss <thomas.voss@canonical.com>
 */

#ifndef MIR_COMPOSITOR_BUFFER_BUNDLE_MANAGER_H_
#define MIR_COMPOSITOR_BUFFER_BUNDLE_MANAGER_H_

#include "mir/compositor/buffer.h"
#include "mir/compositor/buffer_bundle_factory.h"
#include "mir/geometry/size.h"

#include <memory>

namespace mir
{
namespace compositor
{

class BufferAllocationStrategy;
class BufferBundle;
class GraphicBufferAllocator;

class BufferBundleManager : public BufferBundleFactory
{
public:

    explicit BufferBundleManager(
        const std::shared_ptr<BufferAllocationStrategy>& strategy);

    virtual ~BufferBundleManager() {}

    // From BufferBundleFactory
    virtual std::shared_ptr<BufferBundle> create_buffer_bundle(
        geometry::Size size,
        PixelFormat pf);

private:
    std::shared_ptr<BufferAllocationStrategy> buffer_allocation_strategy;

};

}
}


#endif /* MIR_COMPOSITOR_BUFFER_BUNDLE_MANAGER_H_ */
