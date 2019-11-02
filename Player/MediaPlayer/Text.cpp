//
// Created by G on 13/04/2019.
//

#include "Text.h"

Text::Text(shared_ptr<screenManager> screenMng) : Texture(screenMng)
{
}

void Text::setText(std::string text)
{
    if (m_text != text)
    {
        m_text = text;
        m_isDirty = true;
    }
}

void Text::setFontSize(uint16_t fontsize)
{
    if (m_fontSize != fontsize)
    {
        m_fontSize = fontsize;
        m_isDirty = true;
    }
}

void Text::setFontStyle(FontStyle style)
{
    if (m_fontStyle != style)
    {
        m_fontStyle = style;
        m_isDirty = true;
    }
}

void Text::setFontFilename(std::string fontfile)
{
    if (m_fontFile != fontfile)
    {
        m_fontFile = fontfile;
        m_isDirty = true;
    }
}

void Text::formTextureCoordinates(std::vector<GLfloat> &texCoord)
{
    texCoord.push_back(0.0);
    texCoord.push_back(0.0);
    texCoord.push_back(0.0);
    texCoord.push_back(1.0);
    texCoord.push_back(1.0);
    texCoord.push_back(1.0);
    texCoord.push_back(1.0);
    texCoord.push_back(0.0);
}

void Text::render_text()
{
    FT_Face face;

    if (FT_New_Face(m_screenMng->ft, m_fontFile.c_str(), 0, &face))
    {
        fprintf(stderr, "Could not open font\n");
        //return 1;
    }

    FT_Set_Pixel_Sizes(face, 0, m_fontSize);

    const char *p;
    
    uint32_t totalWidth = 0;
    for (p = m_text.c_str(); *p; p++)
    {
        auto a= FT_Load_Char(face, *p, FT_LOAD_RENDER);
        if (!a)
            cout << "failed";
        
        FT_GlyphSlot g = face->glyph;
        totalWidth += g->bitmap.width;
    }
    loadTextureData(totalWidth, 200, NULL, 4);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    uint32_t startPos = 0;
    
    for (p = m_text.c_str(); *p; p++)
    {
        if (!FT_Load_Char(face, *p, FT_LOAD_RENDER))
            cout << "failed";
        
        FT_Bitmap dst;
        auto g = face->glyph;//FT_Bitmap_Convert(m_screenMng->ft, &face->glyph->bitmap, &dst, 4);
        glTexSubImage2D(GL_TEXTURE_2D, 0, startPos, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
        startPos += g->bitmap.width;
    }
}
void Text::tick(float tSecs)
{
    Texture::tick(tSecs);
    if (m_isDirty)
    {
        render_text();
        m_isDirty = false;
    }
}

void Text::render()
{
     glUseProgram(m_screenMng->textProgram);

    glBindBuffer(GL_ARRAY_BUFFER, m_verBuffer);
    GLuint vertexLoc = glGetAttribLocation(m_screenMng->textureProgram, "vVertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, m_textureBuf);
    GLuint texCoorLoc = glGetAttribLocation(m_screenMng->textureProgram, "vTexture");
    glEnableVertexAttribArray(texCoorLoc);
    glVertexAttribPointer(texCoorLoc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    //glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    GLuint samplerLoc = glGetUniformLocation(m_screenMng->textureProgram, "sampler");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(samplerLoc, 0);

    GLuint colorLoc = glGetUniformLocation(m_screenMng->textureProgram, "vColor");
    glUniform4f(colorLoc, m_r, m_g, m_b, m_a);

    auto modelView = glm::translate(m_screenMng->getModelViewMatrix(), getGravity());
    auto mvp = m_screenMng->getProjectionMatrix() * modelView; // m_screenMng->getModelViewMatrix();
    GLuint mvpLoc = glGetUniformLocation(m_screenMng->textureProgram, "mvpMatrix");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(vertexLoc);
    glUseProgram(0);
}
void Text::onWindowRestored()
{
    //m_bLoadTexture = true;
    Element::onWindowRestored();
}
void Text::unload()
{
    Texture::unload();
}
