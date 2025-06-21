#include "TestHelperTestEnvironment.h"

namespace TestHuntTheWumpus
{
    struct TestNotificationChecks
    {
        bool observeWumpusCheck = false;
        bool observePitCheck = false;
        bool observeBatCheck = false;
        bool observeMissCheck = false;
        bool observeOutOfArrowsCheck = false;
        bool batTriggeredCheck = false;
        bool pitTriggeredCheck = false;
        bool wumpusTriggeredCheck = false;
        bool wumpusAwokenCheck = false;
        bool wumpusShotCheck = false;
        bool hunterEatenCheck = false;
        bool hunterShotCheck = false;
        bool caveEnteredCheck = false;
        bool reportIllegalMoveCheck = false;
        bool reportNeighboringCavesCheck = false;
    };

    TestEnvironment::TestEnvironment()
    {
        MakeTestNotifications();
    }

     void TestEnvironment::MakeTestNotifications()
     {
         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveWumpus, [&]() {
             m_testNotifications.observeWumpusCheck == true;
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObservePit, []() {
             std::cout << "I feel a draft!\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveBat, []() {
             std::cout << "Bats nearby!\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveMiss, [&]() {
             auto hunter = std::dynamic_pointer_cast<Hunter>(dungeon.GetCaveDenizens().at({ Category::Hunter, 0 }));
             std::cout << "The Arrow missed. You have " << hunter->ArrowCount() << " Arrows left.\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveOutOfArrows, []() {
             std::cout << "You are out of arrows...\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::BatTriggered, []() {
             std::cout << "Oh no! The Bat has picked you up and carried you to another cave!\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::PitTriggered, []() {
             std::cout << "You feel your feet slip beneath you... you have fallen into a pit! You lose.\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::WumpusTriggered, []() {
             std::cout << "You have accidently stumbled across the Wumpus!\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::WumpusAwoken, []() {
             std::cout << "The Wumpus has been alerted, and it moves to a neighboring cave.\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::WumpusShot, []() {
             std::cout << "Your Arrow hit the mark, the Wumpus has been shot!\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::HunterEaten, []() {
             std::cout << "The mighty Wumpus has caught and consumed you!\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::HunterShot, []() {
             std::cout << "Somehow you shot yourself with your own arrow...\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::CaveEntered, [&]() {
             auto hunterCurrentCave = dungeon.GetCaveDenizens().at({ Category::Hunter, 0 })->GetCurrentCave().lock(); // find the Hunter's cave
             std::cout << "You are in cave: ";
             std::cout << hunterCurrentCave->GetCaveId() << "\n";    // print cave number of the current location of the Hunter
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, []() {
             std::cout << "That move is not possible, please try again.\n";
             });

         m_userNotifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ReportNeighboringCaves, [&]() {
             auto hunterCurrentCave = dungeon.GetCaveDenizens().at({ Category::Hunter, 0 })->GetCurrentCave().lock();  // find the Hunter's cave
             auto connectedLocations = hunterCurrentCave->GetConnectedIds();                                           // get connected Ids

             std::cout << "The caves connected to yours are: ";
             for (auto cave : connectedLocations)    // print number of each connected cave
             {
                 std::cout << cave << " ";
             }
             std::cout << "\n";
             });
     }
}
