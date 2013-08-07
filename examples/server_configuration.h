/*
 * Copyright © 2013 Canonical Ltd.
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
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#ifndef MIR_EXAMPLES_SERVER_CONFIGURATION_H_
#define MIR_EXAMPLES_SERVER_CONFIGURATION_H_

#include "mir/default_server_configuration.h"

namespace mir
{
namespace examples
{

class ServerConfiguration : public DefaultServerConfiguration
{
public:
    ServerConfiguration(int argc, char const** argv);

    std::shared_ptr<graphics::DisplayConfigurationPolicy> the_display_configuration_policy() override;
};

}
}

#endif /* MIR_EXAMPLES_SERVER_CONFIGURATION_H_ */
