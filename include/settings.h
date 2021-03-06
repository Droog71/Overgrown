#ifndef SETTINGS_H
#define SETTINGS_H

extern float difficulty;
extern bool music;
extern bool invert_mouse;
extern double audio_volume;
extern double gui_scale;

void save_settings(std::string cwd);
void load_settings(std::string cwd);

#endif // SETTINGS_H
