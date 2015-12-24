//
// Created by ronald on 24-12-15.
//

#ifndef MACHIAVELLI_COMMANDHANDLER_H
#define MACHIAVELLI_COMMANDHANDLER_H

#include <memory>
#include "GameController.h"

class CommandHandler {
private:
    std::shared_ptr<GameController> gameController;

public:
    CommandHandler(std::shared_ptr<GameController> gameController);

    void handleCommand(ClientCommand command);

    void handleCommandSetup(ClientCommand command);

    void handleCommandInGame(ClientCommand command);
};


#endif //MACHIAVELLI_COMMANDHANDLER_H
