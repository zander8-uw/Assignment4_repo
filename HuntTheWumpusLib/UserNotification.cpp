#include "UserNotification.h"
#include "Dungeon.h"

namespace HuntTheWumpus
{
    void UserNotification::AddCallback([[maybe_unused]] const Notification category, [[maybe_unused]] std::function<void()>&& callback)
    {
        m_callbacks[category].emplace_back(std::move(callback));
    }

    void UserNotification::Notify(Notification category) const
    {
        for (const auto& callback : m_callbacks.at(category))
        {
            callback();
        }
    }
}
