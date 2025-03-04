
#include <ctype.h>
#include <cstdio>
#include <cstdarg>

#include "program.h"
#include "uniforms.h"
#include "image.h"
#include "image_io.h"
#include "texture.h"
#include "image_viewer.h"
#include "window.h"

// Crée une ImageViewer à partir d'un fichier image
ImageViewer create_ImageViewer(const char* filename)
{
    ImageViewer text;

    // Charge l'image
    Image font= read_image( smart_path(filename) );

    // Définit la largeur et la hauteur de la texture
    text.width = font.width() ;
    text.height = font.height() ;
    // Crée la texture de l'image
    text.font = make_texture(0, font);
    // Libère la mémoire occupée par l'image (plus nécessaire car la texture a été créée)
    //~ release_image(font);


    // Charge le shader
    text.program= read_program( smart_path("data/shaders/image.glsl") );
    program_print_errors(text.program);

    // Associe l'uniform buffer à l'entrée 0 / binding 0
    GLint index= glGetUniformBlockIndex(text.program, "textData");
    glUniformBlockBinding(text.program, index, 0);

    // Génère et configure le vertex array object (VAO) et le buffer d'uniforme (UBO)
    glGenVertexArrays(1, &text.vao);
    glGenBuffers(1, &text.ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, text.ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(text.buffer), text.buffer, GL_DYNAMIC_DRAW);

    return text;
}

/*
ImageViewer create_crop_ImageViewer(const char* filename)
{
    ImageViewer text;

    // Charge la fonte
    Image font= read_image( smart_path(filename) );

    text.width = font.width() ;
    text.height = font.height() ;
    // Crée la texture de la fonte
    text.font = make_texture(0, font);
    //~ release_image(font); // Il n'est plus nécessaire de libérer l'image


    // Shader
    text.program= read_program( smart_path("data/shaders/image.glsl") );
    program_print_errors(text.program);

    // Associe l'uniform buffer à l'entrée 0 / binding 0
    GLint index= glGetUniformBlockIndex(text.program, "textData");
    glUniformBlockBinding(text.program, index, 0);

    glGenVertexArrays(1, &text.vao);
    glGenBuffers(1, &text.ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, text.ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(text.buffer), text.buffer, GL_DYNAMIC_DRAW);

    return text;
}
*/

// Libère la mémoire associée à une ImageViewer
void release_ImageViewer( ImageViewer& text )
{
    release_program(text.program);
    glDeleteVertexArrays(1, &text.vao);
    glDeleteBuffers(1, &text.ubo);
    glDeleteTextures(1, &text.font);
}


// Dessine une ImageViewer avec un recadrage spécifié
void draw_crop( const ImageViewer& text, const int width, const int height , int x, int y, float scaleX, float scaleY, float coefMinX, float coefMinY, float coefMaxX, float coefMaxY)
{
    glBindVertexArray(text.vao);
    glUseProgram(text.program);
    program_use_texture(text.program, "font", 0, text.font);

    program_uniform(text.program, "scaleX", scaleX);
    program_uniform(text.program, "scaleY", scaleY);

   //program_uniform(text.program, "offsetX", (width - (text.width *scaleX))/2 + x);
   // program_uniform(text.program, "offsetY", (height - (text.height * scaleY))/2 + y);
    program_uniform(text.program, "offsetX",  x);
    program_uniform(text.program, "offsetY",  (float) height   - y);

    program_uniform(text.program, "coefMinX",  coefMinX);
    program_uniform(text.program, "coefMinY",  coefMinY);
    program_uniform(text.program, "coefMaxX",  coefMaxX);
    program_uniform(text.program, "coefMaxY",  coefMaxY);


    program_uniform(text.program, "dimensionImageX",  text.width);
    program_uniform(text.program, "dimensionImageY",  text.height);
    // Transfère le texte dans l'uniform buffer associé au binding 0, cf create_text()
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, text.ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(text.buffer), text.buffer);

    // Dessine le texte
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

// Dessine une ImageViewer sans recadrage
void draw( const ImageViewer& text, const int width, const int height , int x, int y, float scaleX, float scaleY)
{
    glBindVertexArray(text.vao);
    glUseProgram(text.program);
    program_use_texture(text.program, "font", 0, text.font);

    program_uniform(text.program, "scaleX", scaleX);
    program_uniform(text.program, "scaleY", scaleY);

   //program_uniform(text.program, "offsetX", (width - (text.width *scaleX))/2 + x);
   // program_uniform(text.program, "offsetY", (height - (text.height * scaleY))/2 + y);
   program_uniform(text.program, "offsetX",  x);
    program_uniform(text.program, "offsetY",  (float) height   - y);


    // Transfère le texte dans l'uniform buffer associé au binding 0, cf create_text()
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, text.ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(text.buffer), text.buffer);

    // Dessine le texte
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

// Dessine une ImageViewer avec un fond transparent
void draw_background( const ImageViewer& text, const int width, const int height)
{
    glBindVertexArray(text.vao);
    glUseProgram(text.program);
    program_use_texture(text.program, "font", 0, text.font);

    // Calcule les facteurs de mise à l'échelle pour ajuster l'image au rectangle de dessin
    float scaleX = static_cast<float>(width) / static_cast<float>(text.width);
    float scaleY = static_cast<float>(height) / static_cast<float>(text.height);

    program_uniform(text.program, "scaleX", scaleX);
    program_uniform(text.program, "scaleY", scaleY);

    program_uniform(text.program, "offsetX", (width - (text.width *scaleX))/2 );
    program_uniform(text.program, "offsetY", (height - (text.height * scaleY))/2 );

    // Transfère le texte dans l'uniform buffer associé au binding 0, cf create_text()
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, text.ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(text.buffer), text.buffer);

    // Dessine le texte
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}
