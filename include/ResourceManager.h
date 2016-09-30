///
/// The resource manager
///

#pragma once

// System includes.
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <vector>
// Engine includes.
#include "Manager.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"

namespace df {
	
/// Read single line `tag number', return number
int readLineInt(std::ifstream *p_file, int *p_line_number, std::string tag);
/// Read single line `tag string', return string.
std::string readLineStr(std::ifstream *p_file, int *p_line_number, std::string tag);
/// Read frame until `eof', return Frame.
Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height);
///string to df::Color
Color stringToDfColor(std::string color);
/// Delimiters used to parse Sprite files -
/// the ResourceManager "knows" file format.
const std::string FRAMES_TOKEN = "frames";
const std::string HEIGHT_TOKEN = "height";
const std::string WIDTH_TOKEN = "width";
const std::string COLOR_TOKEN = "color";
const std::string END_FRAME_TOKEN = "end";
const std::string END_SPRITE_TOKEN = "eof";

// Maximum number of unique assets in game.
const int MAX_SPRITES = 1000;
const int MAX_SOUNDS = 128;
const int MAX_MUSICS = 128;
const std::string RESOURCE_MANAGER = "df::RESOURCE_MANAGER";
class ResourceManager : public Manager {

 private:
  ResourceManager (ResourceManager const&); ///< Don't allow copy.
  void operator=(ResourceManager const&);   ///< Don't allow assignment.
  ResourceManager();		 ///< Private since a singleton.
  std::vector<Sprite *> p_sprite; ///< Array of (pointers to) Sprites.
  
  std::vector<Sound> sound;	///< Array of sound buffers.
 
  std::vector<Music *> music;	///< Array of music buffers.


 public:
  /// Get the one and only instance of the ResourceManager.
  static ResourceManager &getInstance();

  /// Get ResourceManager ready to manage resources.
  int startUp();

  /// Shut down manager, freeing up any allocated Sprites, Music and Sounds.
  void shutDown();

  /// Load Sprite from file.
  /// Assign indicated label to Sprite.
  /// Return 0 if ok, else -1.
  int loadSprite(std::string filename, std::string label);

  /// Unload Sprite with indicated label.
  /// Return 0 if ok, else -1.
  int unloadSprite(std::string label);

  /// Find Sprite with indicated label.
  /// Return pointer to it if found, else NULL.
  Sprite *getSprite(std::string label) const;

	/// Load sound from file.
  /// Return 0 if ok, else -1.
  int loadSound(std::string filename, std::string label);

  /// Remove Sound with indicated label.
  /// Return 0 if ok, else -1.
  int unloadSound(std::string label);

  /// Find Sound with indicated label.
  /// Return pointer to it if found, else NULL.
  Sound *getSound(std::string label);

  /// Associate file with Music.
  /// Return 0 if ok, else -1.
  int loadMusic(std::string filename, std::string label);

  /// Remove label for Music with indicated label.
  /// Return 0 if ok, else -1.
  int unloadMusic(std::string label);

  /// Find Music with indicated label.
  /// Return pointer to it if found, else NULL.
  Music *getMusic(std::string label);
};

} // end of namespace df

