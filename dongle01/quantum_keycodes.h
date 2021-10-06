enum quantum_keycodes {
  QK_LAYER_TAP            = 0x4000,
  QK_TO                   = 0x5000,
  QK_MODS                 = 0x0100,
  QK_LCTL                 = 0x0100,
  QK_LSFT                 = 0x0200,
  QK_LALT                 = 0x0400,
  QK_LGUI                 = 0x0800,
  QK_MODS_MAX             = 0x1FFF
};


// Ability to use mods in layouts
#define LCTL(kc) (QK_LCTL | (kc))
#define LSFT(kc) (QK_LSFT | (kc))
#define LALT(kc) (QK_LALT | (kc))
#define LGUI(kc) (QK_LGUI | (kc))
#define LOPT(kc) LALT(kc)
#define LCMD(kc) LGUI(kc)
#define LWIN(kc) LGUI(kc)

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))
#define TO(layer) (QK_TO | ((layer)&0xF) )

#define PICK_CODE(code) ((code) &0xFF)
#define HAS_MOD(code) (QK_MODS < (code) && (code) < QK_MODS_MAX)
#define HAS_LT(code)  (0x4000 <= (code) && (code) <= 0x4FFF)
#define HAS_TO(code)  (0x5000 <= (code) && (code) <= 0x5FFF)
