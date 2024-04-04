#include "game.hpp"
#include <iostream>
#include <memory>
#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);

	FLAGS_logtostderr = 1;
	FLAGS_minloglevel = 0;

    LOG(INFO) << "Starting game with log level: " << FLAGS_minloglevel;

    std::unique_ptr<Game> game = std::make_unique<Game>();

    game->start();

    return 0;
}
