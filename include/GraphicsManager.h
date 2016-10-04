/// Dragonfly - Program a Game Engine from Scratch
///

/// System includes.
#include <SFML/Graphics.hpp>
#include <cstdint>

/// Engine includes.
#include "Color.h"
#include "Manager.h"
#include "Vector.h"
#include "utility.h"
#include "Frame.h"
#pragma once

namespace df
{

enum Justification {
    LEFT_JUSTIFIED,
    CENTER_JUSTIFIED,
    RIGHT_JUSTIFIED,
};
//// Compute character height, based on window size and font.
float charHeight(void);

//// Compute character width, based on window size and font.
float charWidth(void);

//// Convert ASCII spaces (x,y) to window pixels (x,y).
Vector spacesToPixels(Vector spaces);

//// Convert window pixels (x,y) to ASCII spaces (x,y).
Vector pixelsToSpaces(Vector pixels);
/// Defaults for SFML window.
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar | sf::Style::Close;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::White;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";
const std::string GRAPHICS_MANAGER = "df::graphics_manager";
class GraphicsManager : public Manager
{

private:
    GraphicsManager();                       /// Private (a singleton).
    GraphicsManager(GraphicsManager const&); /// Don't allow copy.
    void operator=(GraphicsManager const&);  /// Don't allow assignment
    sf::Font font;                           /// Font used for ASCII graphics.
    sf::RenderWindow* p_window;              /// Pointer to SFML window.
    int window_horizontal_pixels;            /// Horizontal pixels in window.
    int window_vertical_pixels;              /// Vertical pixels in window.
    int window_horizontal_chars;             /// Horizontal ASCII spaces in window.
    int window_vertical_chars;               /// Vertical ASCII spaces in window.

public:
    /// Get the one and only instance of the GraphicsManager.
    static GraphicsManager& getInstance();

    /// Open graphics window ready for text-based display.
    /// Return 0 if ok, else -1.
    int startUp();

    /// Close graphics window.
    void shutDown();

    /// Draw character at window location (x,y) with color.
    /// Return 0 if ok, else -1.
    int drawCh(Vector world_pos, char ch, Color color) const;

	/// Draw wide character at window location (x,y) with color.
    /// Return 0 if ok, else -1.
    int drawWCh(Vector world_pos, wchar_t ch, Color color) const;

    /// Draw string at screen location (x,y) with color.
    /// Justified LEFT, CENTER or RIGHT.
    /// Return 0 if ok, else -1.
    int drawString(Vector world_pos, std::string str, Justification just, Color color) const;

    /// Draw single sprite frame at screen location (x,y) with color.
    /// If centered true then center frame at (x,y).
    /// Return 0 if ok, else -1.
    int drawFrame(Vector world_pos, Frame frame, bool centered, Color color, char transparent = 0) const;

    //// Return window's horizontal maximum (in characters).
    int getHorizontal() const;

    /// Return window's vertical maximum (in characters).
    int getVertical() const;

    /// Return window's horizontal maximum (in pixels).
    int getHorizontalPixels() const;

    /// Return window's vertical maximum (in pixels).
    int getVerticalPixels() const;

    /// Render current window buffer.
    /// Return 0 if ok, else -1.
    int swapBuffers();

    /// Return pointer to SFML drawing window.
    sf::RenderWindow* getWindow() const;
};
}
