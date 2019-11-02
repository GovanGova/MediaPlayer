//
// Created by G on 13/04/2019.
//
#pragma once

#include <Texture.h>

const uint16_t DEFAULT_FONTSIZE = 20;
class Text : public Texture
{
public:
  enum class FontStyle
  {
    REGULAR,
    BOLD,
    ITALIC,
    BOLDITALIC
  };
  Text(shared_ptr<screenManager> screenMng);

  void tick(float tSecs) override;
  void render() override;
  void unload() override;
  void onWindowRestored() override;
  ~Text(){};

  void setText(std::string tet);
  std::string getText() { return m_text; }
  void setFontSize(uint16_t fontsize = DEFAULT_FONTSIZE);
  uint16_t getFontSize() { return m_fontSize; }
  void setFontFilename(std::string fontfile);
  std::string &getFontFilename() { return m_fontFile; }

  void setFontStyle(FontStyle style);
  FontStyle getFontStyle() { return m_fontStyle; }

protected:
  void formTextureCoordinates(std::vector<GLfloat>& tetureCoord);
private:
  void render_text();

  std::string m_text{"Mayil"};
  bool m_isDirty{true};
  uint16_t m_fontSize{DEFAULT_FONTSIZE};
  std::string m_fontFile;
  FontStyle m_fontStyle{FontStyle::REGULAR};
};