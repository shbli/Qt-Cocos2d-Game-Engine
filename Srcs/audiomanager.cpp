#include "audiomanager.h"

bool audioManager::m_musicEnabled = true;
bool audioManager::isAudioPlaybackEnabled = true;
QList <audioInstance> audioManager::m_audioInstanceSounds;

audioManager::audioManager(QObject *parent) :
    QObject(parent)
{

}

void audioManager::setMusicEnabled(bool enabled) {
    m_musicEnabled = enabled;
}

void audioManager::playSound(const QString& path, float volume) {
#ifdef QtMultiMediaKitSupported

    if (isAudioPlaybackEnabled) {
        if  (!path.isEmpty()) {
            //play sound for one time only
#ifdef enableSoundCache
            QSoundEffect* gameSound = sound_cache::shared_sound_cache()->get_sound(path);
#else
            QSoundEffect* gameSound = new QSoundEffect();
            gameSound->setSource(path)
#endif
            if (gameSound != NULL) {
                audioInstance soundInstance;
                soundInstance.audioFileName = path;
                soundInstance.soundInstance = gameSound;
                soundInstance.soundInstance->setVolume(volume);
                soundInstance.soundInstance->play();
                if (volume == 0) {
                    soundInstance.soundInstance->stop();
                }
            }
        }
    }
}
#endif


void audioManager::playLoopSound(const QString& path) {
#ifdef QtMultiMediaKitSupported
    if (isAudioPlaybackEnabled) {
        if  (!path.isEmpty()) {
            //if the loop sound is already playing let's not play it
            for (int i = 0; i < m_audioInstanceSounds.size(); i++) {
                if (m_audioInstanceSounds.at(i).audioFileName == path) {
                    return;
                }
            }

            //play a loop sound here
            QSoundEffect* gameSound = new QSoundEffect();
            gameSound->setSource(path);

            if (gameSound != NULL) {
                audioInstance soundInstance;
                soundInstance.audioFileName = path;
                soundInstance.soundInstance = gameSound;
                soundInstance.soundInstance->setVolume(1.0f);
                soundInstance.soundInstance->play();
                soundInstance.soundInstance->setLoopCount(QSoundEffect::Infinite);
                m_audioInstanceSounds.append(soundInstance);
            }
        }
    }
#endif
}

void audioManager::playMusicLoopSound(const QString& path) {
#ifdef QtMultiMediaKitSupported
    if (m_musicEnabled) {
        //play loop sounds if music is not disabled
        playLoopSound(path);
    }
#endif
}

bool audioManager::stopLoopSound(QString p_audioFileName) {
#ifdef QtMultiMediaKitSupported
    for (int i = 0; i < m_audioInstanceSounds.size(); i++) {
        if (m_audioInstanceSounds.at(i).audioFileName.contains(p_audioFileName)) {
            //stop the loop audio and delete it's object
            if (m_audioInstanceSounds.at(i).soundInstance != NULL) {
                m_audioInstanceSounds.at(i).soundInstance->stop();
                delete m_audioInstanceSounds.at(i).soundInstance;
            }
            m_audioInstanceSounds.removeAt(i);
            return true;
        }
    }
    return false;
#endif
}

void audioManager::setUpAudioManager() {
#ifdef QtMultiMediaKitSupported
    audioManager::enableSounds(true);
#endif

}

void audioManager::enableSounds(bool enable) {
#ifdef QtMultiMediaKitSupported
    isAudioPlaybackEnabled = enable;
    if (!isAudioPlaybackEnabled) {
        while (!m_audioInstanceSounds.isEmpty()) {
            //stop the loop audio and delete it's object
            if (m_audioInstanceSounds.first().soundInstance != NULL) {
                m_audioInstanceSounds.first().soundInstance->stop();
                delete m_audioInstanceSounds.takeFirst().soundInstance;
            } else {
                m_audioInstanceSounds.takeFirst();
            }
        }
    }
#endif
}

/*Sound Cache implementation*/



sound_cache* sound_cache::soundSharedCache = NULL;

//constructor
sound_cache::sound_cache() {
#ifdef debug_sound_cache
    totalCacheSize = 0;
#endif
}

//destructor
sound_cache::~sound_cache() {
    clearCache();
}

sound_cache *sound_cache::shared_sound_cache() {
    if (soundSharedCache == NULL) {
        soundSharedCache = new sound_cache;
    }
    return soundSharedCache;
}

QSoundEffect *sound_cache::get_sound(const QString &sound_file_name) {

    //sound unique cache name
#ifdef enableSoundCache
    std::string hashString = sound_file_name.toStdString();


    sounditerator it = m_SoundCache.find(hashString);
    if(it != m_SoundCache.end()) {
        std::list<SoundStruct>::iterator listIt = it.value();
        Q_ASSERT(listIt != sounds_elements_list.end()); /* It must exist in the list */
        //set the sound as used currently if it was already schedualToDelete
        listIt->soundElementUsage = 1;
        sounds_elements_list.splice( sounds_elements_list.begin(), sounds_elements_list, listIt);
        return  listIt->QSoundEffectPtr;
    }

#endif //no need to search if cache disabled


   //no cached sound matching the same name is found
    QSoundEffect *gameSound = new QSoundEffect();
    gameSound->setSource(QUrl::fromLocalFile(sound_file_name));
    if (gameSound != NULL) {
        SoundStruct tempElemen;
        tempElemen.sound_file_name = sound_file_name;
        tempElemen.QSoundEffectPtr = gameSound;
        tempElemen.soundElementUsage = 1;
#ifdef enableSoundCache
        m_SoundCache[hashString] = sounds_elements_list.insert(sounds_elements_list.end(),tempElemen);
#ifdef debug_sound_cache
        totalCacheSize++;
#endif
        //try to remove none used sounds
        removeLeastUsedElement();
#endif
        return tempElemen.QSoundEffectPtr;
    } else {
        return NULL;
    }
}

void sound_cache::release_sound(const QString& soundToRelease) {
    //sound unique cache name
    std::string hashString = soundToRelease.toStdString();


    sounditerator it = m_SoundCache.find(hashString);
    if(it != m_SoundCache.end()) {
        std::list<SoundStruct>::iterator listIt = it.value();
        Q_ASSERT(listIt != sounds_elements_list.end()); /* It must exist in the list */
        listIt->soundElementUsage = 0;
        //deschedual the sound deletion otherwise it might be dangerose that the sound is going to be deleted twice
        return;
    }
    /* If we get here, the we didn't find the xml document that we wanted to release */
    qDebug() << "Something has gone seriously wrog - sound_cache::release_sound_document(" << soundToRelease << ") called but wasn't found in cache";
    Q_ASSERT(false);
}

void sound_cache::deleteSingleton() {
    delete soundSharedCache;
    soundSharedCache = NULL;
}
void sound_cache::clearCache() {
    while (!sounds_elements_list.empty()) {
        //the element is unused, let's go ahead and remove it
        delete sounds_elements_list.front().QSoundEffectPtr;
        sounds_elements_list.erase(sounds_elements_list.begin());
    }
    m_SoundCache.clear();
}

void sound_cache::removeLeastUsedElement() {
    while (sounds_elements_list.size() > max_number_of_cached_sounds) {
        //we need to remove one element if possible
        if (sounds_elements_list.front().soundElementUsage > 0) {
            break;
        } else {
            //the element is unused, let's go ahead and remove it
#ifdef debug_sound_cache
            totalCacheSize--;
#endif
            Q_ASSERT (sounds_elements_list.front().soundElementUsage >= 0);
            delete sounds_elements_list.front().QSoundEffectPtr;
            sounditerator soundCacheIt = m_SoundCache.find(sounds_elements_list.front().sound_file_name.toStdString());
            Q_ASSERT(soundCacheIt != m_SoundCache.end());
            m_SoundCache.erase(soundCacheIt);
            sounds_elements_list.erase(sounds_elements_list.begin());
        }
    }
#ifdef debug_sound_cache
    print_all_elements();
#endif
}

#ifdef debug_sound_cache
void sound_cache::print_all_elements() {
        qDebug() << "Cache sound count = " << sounds_elements_list.size();
//        qDebug() << "Cache total size in bytes = " << totalCacheSize;
//        qDebug() << "Cache total size in mega bytes = " << totalCacheSize/1024.0/1024.0;
}
#endif
