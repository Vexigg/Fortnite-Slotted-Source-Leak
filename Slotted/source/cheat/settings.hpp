#pragma once

inline static const char* CurrentWeaponCfg = "Rifle";
inline const char* WeaponCfgs[] = { "Rifle", "Shotgun", "Smg", "Pistol", "Sniper" };

inline int norm_hitbox = 0;
inline const char* norm_Hitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };

inline int CurrentHitbox = 0;
inline const char* Hitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };

inline int CurrentCloseHitbox = 0;
inline const char* CloseHitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };

inline int RifleCurrentHitbox = 1;
inline const char* RifleHitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
inline int ShotgunCurrentHitbox = 0;
inline const char* ShotgunHitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
inline int SmgCurrentHitbox = 1;
inline const char* SmgHitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
inline int PistolCurrentHitbox = 1;
inline const char* PistolHitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
inline int SniperCurrentHitbox = 1;
inline const char* SniperHitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
bool enemiesarround = true;
int enemyID = 0;
int enemyIDvis = 0;
int CloseRangeDistanceID = 0;
float CloseRangeDistance = 50.f;
static int menu_animation = 0;
static int border_animation = 0;
static int menu_slide = 0;

inline bool menu_open = false;
inline bool debug = true;
inline bool v_sync = true;
inline bool enabletab = false;
inline bool enabletab2 = false;
inline bool enabletab3 = false;
inline bool memaim = false;
inline bool aimbot = true;
inline float smoothing = 15;
inline int target_bone = 0;
inline int fov = 250;
inline bool draw_fov = false;
inline int max_aimbot_distance = 250;
inline bool triggerbot = true;
inline bool targetline = false;
inline bool weaponconfigs = false;
inline int aimdelay = 0;

inline int norm_fov = 8;
inline int norm_smooth = 19;

inline int smoothness1 = 13;
inline int smoothness2 = 6;
inline int smoothness3 = 11;
inline int smoothness4 = 12;
inline int smoothness5 = 4;

inline int fov1 = 13;
inline int fov2 = 9;
inline int fov3 = 10;
inline int fov4 = 11;
inline int fov5 = 8;

inline int real_hitbox;
inline int real_smooth;

inline bool CRFOV = false;
inline int distance69 = 10;
inline bool close_distance = false;
inline int close_fov = 13;
inline float close_smooth = 4;
inline int close_hitbox = 0;
inline int AimSpeedCloseRange = 14;

inline bool memyaim = false;
inline bool esp = true;
inline bool box_esp = true;
inline bool box_outline = false;
inline bool box_round = false;
inline bool box_corner = false;
inline bool line = false;
inline bool skeleton = false;
inline bool draw_username = true;
inline bool draw_platform = false;
inline bool draw_distance = false;
inline bool draw_held_weapon = false;
inline int box_type = 0;
inline float box_outline_thickness = 2.5;
inline int max_esp_distance = 250;



inline bool draw_crosshair = false;
inline bool draw_fps = true;
inline bool draw_watermark = true;
inline bool show_console = false;
inline bool obs_bypass = false;
inline bool nazi_mode = false;
inline float Resx = 1920;
inline float Resy = 1080;
inline float skel_thickness = 1;
inline float box_thickness = 1;
inline float linethickness = 1;
float visible_color_float[4] = { 1.f, 0.f, 0.f, 1.f };
float invisible_color_float[4] = { 1.f, 0.f, 0.f, 1.f };
float customImguiBack[4] = { 1.f, 0.f, 0.f, 1.f };
float customImguiFront[4] = { 0.15f, 0.15f, 0.15f, 1.0f };

