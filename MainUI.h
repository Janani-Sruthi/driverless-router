#ifndef MAIN_UI_H
#define MAIN_UI_H

#include "RoutePlanner.h"

// Owns the RoutePlanner and drives the console menu loop. All user I/O
// lives here so RoutePlanner and the entity/manager classes stay free of
// any UI concerns.
class MainUI {
private:
    RoutePlanner planner;

    void handleAddEditDelete();
    void printMenu() const;
    void listShuttles();
    void listPassengers();

public:
    void renderLoop();
};

#endif
