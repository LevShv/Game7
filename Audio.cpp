#include "Audio.h"
#include "file_tools.h"


//std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
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


track::~track()
{
    delete loaded_track;
}
