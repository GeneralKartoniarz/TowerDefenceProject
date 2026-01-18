#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class MusicManager
{
public:
    MusicManager() = default;

    struct Track
    {
        string key;
        sf::Music* music;
    };

    bool LoadMusic(string key, const string& filepath)
    {
        sf::Music* music = new sf::Music();
        if (!music->openFromFile(filepath))
        {
            delete music;
            return false;
        }

        music->setLooping(true);
        tracks.push_back({ key, music });
        return true;
    }

    void Play(string key)
    {
        if (currentKey == key) return;

        Stop();

        for (auto& t : tracks)
        {
            if (t.key == key)
            {
                t.music->setVolume(20);
                t.music->play();
                
                currentKey = key;
                return;
            }
        }
    }

    void Stop()
    {
        if (currentKey != "")
        {
            for (auto& t : tracks)
            {
                if (t.key == currentKey)
                {
                    t.music->stop();
                    break;
                }
            }
            currentKey = "";
        }
    }

    void Pause()
    {
        for (auto& t : tracks)
        {
            if (t.key == currentKey)
            {
                t.music->pause();
                break;
            }
        }
    }

    void Resume()
    {
        for (auto& t : tracks)
        {
            if (t.key == currentKey)
            {
                t.music->play();
                break;
            }
        }
    }

    ~MusicManager()
    {

    }

private:
    vector<Track> tracks;
    string currentKey = "";
};
