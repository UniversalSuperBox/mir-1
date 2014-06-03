/*
 * Copyright © 2014 Canonical Ltd.
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
 * Authored By: Nick Dedekind <nick.dedekind@canonical.com>
 */

#ifndef MIR_TEST_DOUBLES_MOCK_TRUST_SESSION_LISTENER_H_
#define MIR_TEST_DOUBLES_MOCK_TRUST_SESSION_LISTENER_H_

#include "mir/scene/trust_session_listener.h"

#include <gmock/gmock.h>

namespace mir
{
namespace test
{
namespace doubles
{

struct MockTrustSessionListener : public scene::TrustSessionListener
{
    virtual ~MockTrustSessionListener() noexcept(true) {}

    MOCK_METHOD1(starting, void(std::shared_ptr<scene::TrustSession> const&));
    MOCK_METHOD1(stopping, void(std::shared_ptr<scene::TrustSession> const&));

    MOCK_METHOD2(participant_added, void(scene::TrustSession const&, std::shared_ptr<scene::Session> const&));
    MOCK_METHOD2(participant_removed, void(scene::TrustSession const&, std::shared_ptr<scene::Session> const&));
};

}
}
} // namespace mir

#endif // MIR_TEST_DOUBLES_MOCK_TRUST_SESSION_LISTENER_H_
