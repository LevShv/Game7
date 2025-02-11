#include "Audio.h"
#include "file_tools.h"

void track::play(std::string song)
{
    loaded_track = new sf::Music();
    file_tools* ft = new file_tools();
    std::string path = ft->music_directory() + '/';

    if (!loaded_track->openFromFile(ft->music_directory() + '/' + song)) {
        return;
    }

    loaded_track->setLoop(true);
    loaded_track->play();
}

void track::stop()
{
    loaded_track->stop();
}

sound::sound() {

    step = new sf::Music();
    file_tools* ft = new file_tools();
    std::string path = ft->music_directory() + '/';

    if (!step->openFromFile(ft->sounds_directory() + '/' + "step.wav")) {
        return;
    }
}
track::~track()
{
    delete loaded_track;
}

void sound::play(sf::Music* thing)
{
    thing->play();
}
