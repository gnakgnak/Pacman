// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
ALLEGRO_BITMAP * button_pack;
static int settings_w ;
static int settings_h ;
static ALLEGRO_SAMPLE *settingMusic;
Button btnsettings1;
Button soundUp;
Button soundDown;
Button upup;
Button back;
static ALLEGRO_SAMPLE_ID settings_bgm;

static void init() {
    settingMusic = load_audio("Assets/Music/original_theme.ogg");
    button_pack = load_bitmap("Assets/settings_background.png");
    btnsettings1 = button_create(320, 210, 50, 50, "Assets/Down.png","Assets/Down1.png");
    soundUp = button_create(320, 350, 50, 50, "Assets/Up.png", "Assets/Up1.png");
    soundDown = button_create(320, 410, 50, 50, "Assets/Down.png", "Assets/Down1.png");
    upup = button_create(320, 160, 50, 50, "Assets/Up.png", "Assets/Up1.png");
    back = button_create(320, 495,100, 80, "Assets/backset.png", "Assets/setset.png");
    settings_w = al_get_bitmap_width(button_pack);
    settings_h = al_get_bitmap_height(button_pack);
    stop_bgm(settings_bgm);
    settings_bgm = play_bgm(settingMusic, music_volume);
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
    btnsettings1.hovered = buttonHover(btnsettings1, mouse_x, mouse_y);
    soundUp.hovered = buttonHover(soundUp, mouse_x, mouse_y);
    soundDown.hovered = buttonHover(soundDown, mouse_x, mouse_y);
    upup.hovered = buttonHover(upup, mouse_x, mouse_y);
    back.hovered = buttonHover(back, mouse_x, mouse_y);
}
static void draw(void ){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    const float scale = 1.3;
    const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * settings_w;
    const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * settings_h;
    al_draw_scaled_bitmap(button_pack,0,0,settings_w,settings_h,offset_w,offset_h,settings_w*scale,settings_h*scale,0);
    drawButton(btnsettings1);
    drawButton(soundUp);
    drawButton(soundDown);
    drawButton(upup);
    drawButton(back);
    
}
char music[15];
static void on_mouse_down() {
    if (soundUp.hovered&& music_volume <=1.5)
        music_volume+=0.1;
        
    if(soundDown.hovered&& music_volume > 0)
        music_volume -= 0.1;

        
    if(upup.hovered&& effect_volume <=1.5)
        effect_volume+=0.1;

    if(btnsettings1.hovered && effect_volume>0)
        effect_volume -=0.1;
    if(back.hovered){
        stop_bgm(settings_bgm);
        game_change_scene(scene_menu_create());
    }
}
static void destroy(){
    al_destroy_bitmap(back.hovered_img);
    al_destroy_bitmap(back.default_img);
    al_destroy_bitmap(upup.hovered_img);
    al_destroy_bitmap(upup.default_img);
    al_destroy_bitmap(btnsettings1.default_img);
    al_destroy_bitmap(btnsettings1.hovered_img);
    al_destroy_sample(settingMusic);
    al_destroy_bitmap(soundUp.hovered_img);
    al_destroy_bitmap(soundUp.default_img);
    al_destroy_bitmap(soundDown.default_img);
    al_destroy_bitmap(soundDown.hovered_img);
    al_destroy_bitmap(button_pack);
    
}

Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
//    scene.update;
    scene.initialize = &init;
    scene.draw = &draw;
    scene.on_mouse_down = &on_mouse_down;
    scene.on_mouse_move=&on_mouse_move;
    scene.destroy = &destroy;
//    scene.on_key_down=&on_key_down;
    // TODO: Register more event callback functions such as keyboard, mouse, ...
//
//    drawButton(btnsettings1);
//    al_draw_scaled_bitmap(button_pack, 0, 0,16, 16,25,25,100,100, 0);
	game_log("Settings scene created");
	return scene;
}
