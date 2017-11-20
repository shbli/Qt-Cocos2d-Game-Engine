#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QDebug>
#include <QTimer>

//this is set to exclude some devices (Like android) which still doesn't support QtMultiMediaKit
#ifndef Q_WS_QPA
#ifndef harmattan
#define QtMultiMediaKitSupported
#endif
#endif

#ifdef Q_OS_MAC
#define QtMultiMediaKitSupported
#endif

#ifdef QtMultiMediaKitSupported
#include <QSoundEffect>
#endif

#define enableSoundCache
#define max_number_of_cached_sounds 30
//#define debug_sound_cache

struct audioInstance {
    QString audioFileName;
    QSoundEffect* soundInstance;
};



/*
Sound Cache needed
*/


struct SoundStruct {
    QSoundEffect* QSoundEffectPtr;
    int soundElementUsage;
    QString sound_file_name;
};


typedef QMap<std::string,std::list<SoundStruct>::iterator>::iterator sounditerator;

class sound_cache
{
public:

    ~sound_cache();
    static sound_cache* shared_sound_cache();
    static void deleteSingleton();
    QSoundEffect* get_sound(const QString &sound_file_name);
    void release_sound(const QString& sound);
    void clearCache();

private:

    std::list<SoundStruct> sounds_elements_list;

    QMap <std::string , std::list<SoundStruct>::iterator> m_SoundCache;

    static sound_cache* soundSharedCache;
    sound_cache();
    void removeLeastUsedElement();
#ifdef debug_sound_cache
    void print_all_elements();
    int totalCacheSize;
#endif
};



class audioManager : public QObject
{
    Q_OBJECT
public:
    static void playSound(const QString& path, float volume = 1.0f);
    static void playLoopSound(const QString& path);
    //this is a dummy function of the above, except that it's name is special for music and can be disabled using setMusicEnabled(false) without affecting other loop sounds, stopping this sound is the same as a loop sound
    static void playMusicLoopSound(const QString& path);
    static bool stopLoopSound(QString p_audioFileName);

    static void setUpAudioManager();
    static void enableSounds(bool);
    static void setMusicEnabled(bool enabled);
private:

    explicit audioManager(QObject *parent = 0);
    static QList <audioInstance> m_audioInstanceSounds;
    static bool m_musicEnabled;
    static bool isAudioPlaybackEnabled;

};

#endif // AUDIOMANAGER_H
